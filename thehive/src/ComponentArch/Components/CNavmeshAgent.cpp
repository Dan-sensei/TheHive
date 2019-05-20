#include "CNavmeshAgent.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>
#include <cmath>
#include "CRigidBody.hpp"
#include <ComponentArch/Components/CAIEnem.hpp>

//#define MAXSPEED 4.f
#define FORCE_FACTOR 250.f

//aqui
CNavmeshAgent::CNavmeshAgent()
:Engine(nullptr), cTransform(nullptr), currentWaypointID(11), currentlyMovingTowardsTarget(false), SightDistance(250000)
{

}

CNavmeshAgent::~CNavmeshAgent() {

}


void CNavmeshAgent::Init(){
    //  We check if this entity has the TRANSFORM component
    Engine = Singleton<Omicron>::Instance();
    MHandler_SETPTRS();
    ObjectManager* Manager=Singleton<ObjectManager>::Instance();
    CAIEnem* ia=static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM, getEntityID()));
    if(ia){
        vel=ia->getVelocity();
    }else{
        vel=0;
    }
}


gg::EMessageStatus CNavmeshAgent::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CNavmeshAgent::MHandler_SETPTRS(){
    cRigidBody = static_cast<CRigidBody*>(Singleton<ObjectManager>::Instance()->getComponent(gg::RIGID_BODY, getEntityID()));
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    world = Singleton<ggDynWorld>::Instance();
    return gg::ST_TRUE;
}

void CNavmeshAgent::Update(){
    //  Debug!
    //Engine->Draw3DLine(cTransform->getPosition() + glm::vec3(0, 5, 0), cTransform->getPosition()+(moveVector*100.f)+glm::vec3(0, 5, 0), gg::Color(255,0,0,1));
    //Engine->Draw3DLine(cTransform->getPosition() + glm::vec3(0, 5, 0), cTransform->getPosition()+(glm::normalize(cRigidBody->getVelocity())*100.f)+glm::vec3(0, 5, 0), gg::Color(255,255,0,1));

    if(Singleton<Pathfinding>::Instance()->isDebugging() && !Waypoints.empty()){

        std::stack<Waypoint> debug = Waypoints;

        gg::Color color;
        color.R = 10;
        color.G = 255;
        color.B = 200;
        color.Alpha = 1;

        //Engine->Draw3DLine(cTransform->getPosition() + glm::vec3(0, 5, 0), debug.top().Position + glm::vec3(0, 10, 0), color);
        while(!debug.empty()){
            Waypoint first = debug.top();
            debug.pop();
            if(debug.empty())
            break;

            Waypoint second = debug.top();
            //Engine->Draw3DLine(first.Position + glm::vec3(0, 10, 0), second.Position + glm::vec3(0, 10, 0), color);
        }
    }

}

void CNavmeshAgent::FixedUpdate(){

    if(!cTransform || !currentlyMovingTowardsTarget)  return;

    moveVector = Waypoints.top().Position - cTransform->getPosition();

    //  Check if we can skip some nodes, but just if 0.15 seconds have passed
    if(Timer.ElapsedTime().Seconds() > 0.3) CheckShortcut();

    float modulo= glm::length(moveVector);

    // Check if we are close to the next destination node
    if(modulo <= 7) {
        currentWaypointID = Waypoints.top().ID;
        Waypoints.pop();

        //  If it's last
        if(Waypoints.empty()){
            // Stop moving
            currentlyMovingTowardsTarget = false;
            glm::vec3 Counter = glm::vec3(cRigidBody->getXZVelocity().x * -0.7f, 0, cRigidBody->getXZVelocity().y * -0.7f)*FORCE_FACTOR;
            cRigidBody->applyCentralForce(Counter);
            //cRigidBody->setLinearVelocity(glm::vec3());//para solo velocidades
        }

        return;
    }

    moveVector = (moveVector / modulo);

    //  Apply a counter force when we change direction, so we can stop on curves
    ApplyCouterForce(moveVector);


    //if(glm::length(cRigidBody->getXZVelocity()) < vel)
    //   cRigidBody->applyCentralForce(moveVector*FORCE_FACTOR*1.5);



    cRigidBody->applyConstantVelocityNormal(moveVector,vel);//para solo velocidades

    // if(glm::length(cRigidBody->getXZVelocity()) < MAXSPEED)
    //     cRigidBody->applyCentralForce(moveVector*FORCE_FACTOR*1.5f);


}

void CNavmeshAgent::CheckShortcut(){
    bool stop = false;

    do{
        if(Waypoints.size() == 1) break;

        Waypoint backup = Waypoints.top();
        Waypoints.pop();

        //  If the node is less than the sight distance, and we can see it without problems, then go directly to that Waypoint
        if( gg::FastDIST(cTransform->getPosition(), Waypoints.top().Position) > SightDistance ||
            world->DoesItHitSomething(cTransform->getPosition() + glm::vec3(0, 2, 0), Waypoints.top().Position + glm::vec3(0, 2, 0))
        ){
            Waypoints.push(backup);
            stop = true;
        }
    } while(!stop);

    Timer.Restart();
}

void CNavmeshAgent::ApplyCouterForce(const glm::vec3 &DirVector){
    glm::vec2 XZVelocity = glm::normalize(cRigidBody->getXZVelocity());

    float dot = DirVector.x * XZVelocity.x  +  DirVector.z * XZVelocity.y;
    float det = DirVector.x * XZVelocity.y  -  DirVector.z * XZVelocity.x;
    float angle = atan2(det, dot);

    glm::vec3 Counter = glm::vec3();
    if(cos(angle) < 0.98) {
        Counter = glm::vec3(cRigidBody->getXZVelocity().x * -0.12f, 0, cRigidBody->getXZVelocity().y * -0.12f)*FORCE_FACTOR*(abs(sin(angle))*1.2f);
        cRigidBody->applyCentralForce(Counter);
    }
}

void CNavmeshAgent::SetDestination(const glm::vec3 &Target){
    Waypoints = std::stack<Waypoint>();
    Singleton<Pathfinding>::Instance()->FindPath(cTransform->getPosition(), Target, Waypoints);
    if(Waypoints.empty()){
        ////std::cout << "EMPTY!" << '\n';
        currentlyMovingTowardsTarget = false;
        cRigidBody->setLinearVelocity(glm::vec3(0.5));
        return;
    }
    CheckShortcut();
    Timer.Restart();
    currentlyMovingTowardsTarget = true;
}

bool CNavmeshAgent::HasDestination(){
    return currentlyMovingTowardsTarget;
}

void CNavmeshAgent::ResetDestination(){
    Waypoints = std::stack<Waypoint>();
    currentlyMovingTowardsTarget = false;
}
