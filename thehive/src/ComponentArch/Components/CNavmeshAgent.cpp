#include "CNavmeshAgent.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>
#include <cmath>

CNavmeshAgent::CNavmeshAgent()
:Engine(nullptr), cTransform(nullptr), currentWaypointID(11), currentlyMovingTowardsTarget(false), SightDistance(300000)
{

}

CNavmeshAgent::~CNavmeshAgent() {

}

void CNavmeshAgent::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::NAVMESHAGENT, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::NAVMESHAGENT, gg::M_SETPTRS);
}

void CNavmeshAgent::Init(){
    //  We check if this entity has the TRANSFORM component
    Engine = Singleton<GameEngine>::Instance();
    MHandler_SETPTRS();
}


gg::EMessageStatus CNavmeshAgent::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

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

#define MAXSPEED 20.f
#define FORCE_FACTOR 600.f

gg::EMessageStatus CNavmeshAgent::MHandler_UPDATE(){

    if(!cTransform)     return gg::ST_ERROR;
    if(!currentlyMovingTowardsTarget) return gg::ST_IGNORED;

    gg::Vector3f* target = &Waypoints.top().Position;
    gg::Vector3f moveVector = *target - cTransform->getPosition();

    float modulo= gg::Modulo(moveVector);

    bool stop = false;

    do{
        if(Waypoints.size() == 1) break;

        Waypoint backup = Waypoints.top();
        Waypoints.pop();

        if( gg::FastDIST(cTransform->getPosition(), Waypoints.top().Position) > SightDistance ||
            world->DoesItHitSomething(cTransform->getPosition() + gg::Vector3f(0, 10, 0), Waypoints.top().Position + gg::Vector3f(0, 10, 0))
        ){

            Waypoints.push(backup);
            stop = true;
        }
    } while(!stop);


    if(modulo <= MAXSPEED) {
        currentWaypointID = Waypoints.top().ID;
        Waypoints.pop();
        if(Waypoints.empty()){
            currentlyMovingTowardsTarget = false;
            gg::Vector3f Counter = gg::Vector3f(cRigidBody->getXZVelocity().X * -0.7, 0, cRigidBody->getXZVelocity().Y * -0.7)*FORCE_FACTOR;
            cRigidBody->applyCentralForce(Counter);
        }

        return gg::ST_TRUE;
    }

    moveVector = (moveVector / modulo)*FORCE_FACTOR;

    //  Debug!
    Engine->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 10, 0), cTransform->getPosition()+(moveVector/FORCE_FACTOR)*100+gg::Vector3f(0, 10, 0), gg::Color(0,255,0,1));
    Engine->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 10, 0), cTransform->getPosition()+gg::Vector3f(0, 10, 0)+cRigidBody->getVelocity()*5, gg::Color(255,255,0,1));

    gg::Vector2f XZVelocity = gg::Normalice(cRigidBody->getXZVelocity());

    float dot = moveVector.X * XZVelocity.X  +  moveVector.Z * XZVelocity.Y;
    float det = moveVector.X * XZVelocity.Y  -  moveVector.Z * XZVelocity.X;
    float angle = atan2(det, dot);

    gg::Vector3f Counter = gg::Vector3f();
    if(abs(cos(angle)) < 0.9) {
        Counter = gg::Vector3f(cRigidBody->getXZVelocity().X * -0.12, 0, cRigidBody->getXZVelocity().Y * -0.12)*FORCE_FACTOR*abs(sin(angle));
        cRigidBody->applyCentralForce(Counter);
    }

    if(gg::Modulo(cRigidBody->getXZVelocity()) < MAXSPEED)
        cRigidBody->applyCentralForce(moveVector);

    if(Singleton<Pathfinding>::Instance()->isDebugging()){
        std::stack<Waypoint> debug = Waypoints;
        gg::Color color;
        color.R = 10;
        color.G = 255;
        color.B = 200;
        color.Alpha = 1;

        Singleton<GameEngine>::Instance()->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 5, 0), debug.top().Position + gg::Vector3f(0, 40, 0), color, 2);
        while(!debug.empty()){
            Waypoint first = debug.top();
            debug.pop();
            if(debug.empty())
                break;

            Waypoint second = debug.top();
            Singleton<GameEngine>::Instance()->Draw3DLine(first.Position + gg::Vector3f(0, 40, 0), second.Position + gg::Vector3f(0, 40, 0), color, 2);
        }

    }


    return gg::ST_TRUE;
}

void CNavmeshAgent::SetDestination(const gg::Vector3f &Target){
    Singleton<Pathfinding>::Instance()->FindPath(cTransform->getPosition(), Target, Waypoints);
    if(Waypoints.empty()){
        gg::cout("No hay camino");
        return;
    }
    currentlyMovingTowardsTarget = true;
}

bool CNavmeshAgent::HasDestination(){
    return currentlyMovingTowardsTarget;
}