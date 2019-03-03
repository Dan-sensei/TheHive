#include "CNavmeshAgent.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>
#include <cmath>
#include "CRigidBody.hpp"

#define MAXSPEED 4.f
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
    Engine = Singleton<TMotorTAG>::Instance();
    MHandler_SETPTRS();
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
    Engine->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 5, 0), cTransform->getPosition()+(moveVector*100)+gg::Vector3f(0, 5, 0), gg::Color(255,0,0,1));
    Engine->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 5, 0), cTransform->getPosition()+(gg::Normalice(cRigidBody->getVelocity())*100)+gg::Vector3f(0, 5, 0), gg::Color(255,255,0,1));

    if(Singleton<Pathfinding>::Instance()->isDebugging() && !Waypoints.empty()){

        std::stack<Waypoint> debug = Waypoints;

        gg::Color color;
        color.R = 10;
        color.G = 255;
        color.B = 200;
        color.Alpha = 1;

        Engine->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 5, 0), debug.top().Position + gg::Vector3f(0, 10, 0), color);
        while(!debug.empty()){
            Waypoint first = debug.top();
            debug.pop();
            if(debug.empty())
            break;

            Waypoint second = debug.top();
            Engine->Draw3DLine(first.Position + gg::Vector3f(0, 10, 0), second.Position + gg::Vector3f(0, 10, 0), color);
        }
    }

}

void CNavmeshAgent::FixedUpdate(){

    if(!cTransform || !currentlyMovingTowardsTarget)  return;

    moveVector = Waypoints.top().Position - cTransform->getPosition();

    //  Check if we can skip some nodes, but just if 0.15 seconds have passed
    if(Timer.ElapsedTime().Seconds() > 0.3) CheckShortcut();

    float modulo= gg::Modulo(moveVector);

    // Check if we are close to the next destination node
    if(modulo <= 10) {
        currentWaypointID = Waypoints.top().ID;
        Waypoints.pop();

        //  If it's last
        if(Waypoints.empty()){
            // Stop moving
            currentlyMovingTowardsTarget = false;
            gg::Vector3f Counter = gg::Vector3f(cRigidBody->getXZVelocity().X * -0.7, 0, cRigidBody->getXZVelocity().Y * -0.7)*FORCE_FACTOR;
            cRigidBody->applyCentralForce(Counter);
        }

        return;
    }

    moveVector = (moveVector / modulo);

    //  Apply a counter force when we change direction, so we can stop on curves
    ApplyCouterForce(moveVector);

    if(gg::Modulo(cRigidBody->getXZVelocity()) < MAXSPEED)
        cRigidBody->applyCentralForce(moveVector*FORCE_FACTOR*1.5);

}

void CNavmeshAgent::CheckShortcut(){
    bool stop = false;

    do{
        if(Waypoints.size() == 1) break;

        Waypoint backup = Waypoints.top();
        Waypoints.pop();

        //  If the node is less than the sight distance, and we can see it without problems, then go directly to that Waypoint
        if( gg::FastDIST(cTransform->getPosition(), Waypoints.top().Position) > SightDistance ||
            world->DoesItHitSomething(cTransform->getPosition() + gg::Vector3f(0, 2, 0), Waypoints.top().Position + gg::Vector3f(0, 2, 0))
        ){
            Waypoints.push(backup);
            stop = true;
        }
    } while(!stop);

    Timer.Restart();
}

void CNavmeshAgent::ApplyCouterForce(const gg::Vector3f &DirVector){
    gg::Vector2f XZVelocity = gg::Normalice(cRigidBody->getXZVelocity());

    float dot = DirVector.X * XZVelocity.X  +  DirVector.Z * XZVelocity.Y;
    float det = DirVector.X * XZVelocity.Y  -  DirVector.Z * XZVelocity.X;
    float angle = atan2(det, dot);

    gg::Vector3f Counter = gg::Vector3f();
    if(cos(angle) < 0.98) {
        Counter = gg::Vector3f(cRigidBody->getXZVelocity().X * -0.12, 0, cRigidBody->getXZVelocity().Y * -0.12)*FORCE_FACTOR*(abs(sin(angle))*1.2);
        cRigidBody->applyCentralForce(Counter);
    }
}

void CNavmeshAgent::SetDestination(const gg::Vector3f &Target){
    Waypoints = std::stack<Waypoint>();
    Singleton<Pathfinding>::Instance()->FindPath(cTransform->getPosition(), Target, Waypoints);
    if(Waypoints.empty()){
        currentlyMovingTowardsTarget = false;
        cRigidBody->setLinearVelocity(0.5);
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
    while(!Waypoints.empty()){
        Waypoints.pop();
    }

    currentlyMovingTowardsTarget = false;
}
