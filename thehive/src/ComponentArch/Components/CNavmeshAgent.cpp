#include "CNavmeshAgent.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>

CNavmeshAgent::CNavmeshAgent(gg::Vector3f _Size)
:Engine(nullptr), cTransform(nullptr), currentWaypointID(11), currentlyMovingTowardsTarget(false), SightDistance(200000), Size(_Size)
{
}

CNavmeshAgent::~CNavmeshAgent() {

}


void CNavmeshAgent::Init(){
    //  We check if this entity has the TRANSFORM component
    Engine = Singleton<GameEngine>::Instance();
    MHandler_SETPTRS();
}


gg::EMessageStatus CNavmeshAgent::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();
    else if(m.mType == gg::M_NEW_POSITION) return MHandler_SETNEWPOSITION(m);

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

gg::EMessageStatus CNavmeshAgent::MHandler_SETNEWPOSITION(const Message &m){
    gg::Vector3f Destination = *static_cast<gg::Vector3f*>(m.mData);
    SetDestination(Destination);
    return gg::ST_TRUE;
}

#define MAXSPEED 30.f
#define FORCE_FACTOR 2500.f

void CNavmeshAgent::Update(){
    // PURE DEBUGGING {
        if(Singleton<Pathfinding>::Instance()->isDisplayPathEnabled() && !Waypoints.empty()){
            std::stack<Waypoint> debug = Waypoints;
            gg::Color color;
            color.R = 10;
            color.G = 255;
            color.B = 200;
            color.Alpha = 1;

            Singleton<GameEngine>::Instance()->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 5, 0), debug.top().Position + gg::Vector3f(0, 40, 0), color, 2);
            while(!debug.empty()){
                //std::cout << "Debug Broken" << '\n';
                Waypoint first = debug.top();
                debug.pop();
                if(debug.empty())
                    break;

                Waypoint second = debug.top();
                Singleton<GameEngine>::Instance()->Draw3DLine(first.Position + gg::Vector3f(0, 40, 0), second.Position + gg::Vector3f(0, 40, 0), color, 2);
            }
        }

        if(Singleton<Pathfinding>::Instance()->isDisplayVectorsEnabled()){
            Engine->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 10, 0), cTransform->getPosition()+(DebugMoveVector*100)+gg::Vector3f(0, 7, 0), gg::Color(255,0,0,1));
            Engine->Draw3DLine(cTransform->getPosition() + gg::Vector3f(0, 10, 0), cTransform->getPosition()+(gg::Normalice(cRigidBody->getVelocity())*100)+gg::Vector3f(0, 10, 0), gg::Color(255,255,0,1));

            gg::Vector3f Increment(DebugMoveVector.X*50, 0, DebugMoveVector.Z*50);
            Engine->Draw3DLine(RS, RS + Increment , gg::Color(204, 51, 0), 2);
            Engine->Draw3DLine(LS, LS + Increment , gg::Color(204, 51, 0), 2);
        }
    // }
}

void CNavmeshAgent::FixedUpdate(){
    if(!cTransform || !currentlyMovingTowardsTarget)  return;
    //std::cout << "Updating" << '\n';
    gg::Vector3f moveVector = Waypoints.top().Position - cTransform->getPosition();

    //  Check if we can skip some nodes, but just if 0.5 seconds have passed
    if(Timer.ElapsedTime().Seconds() > 0.25) CheckShortcut();

    float modulo= gg::Modulo(moveVector);

    // Check if we are close to the next destination node
    if(modulo <= 35) {
        currentWaypointID = Waypoints.top().ID;
        Waypoints.pop();

        //  If it's last
        if(Waypoints.empty()){
            // Stop moving
            currentlyMovingTowardsTarget = false;
            gg::Vector3f Counter = gg::Vector3f(cRigidBody->getXZVelocity().X * -0.12, 0, cRigidBody->getXZVelocity().Y * -0.12)*FORCE_FACTOR;
            cRigidBody->applyCentralForce(Counter);
        }

        return;
    }

    moveVector = (moveVector / modulo);
    DebugMoveVector = moveVector;   // <- Debug things

    CheckForSideCollisions(moveVector);

    moveVector *= FORCE_FACTOR;
    //  Apply a counter force when we change direction, so we can stop on curves
    ApplyCouterForce(moveVector);

    if(gg::Modulo(cRigidBody->getXZVelocity()) < MAXSPEED)
        cRigidBody->applyCentralForce(moveVector);
}

void CNavmeshAgent::CheckShortcut(){
    bool stop = false;

    do{
        if(Waypoints.size() == 1) break;

        Waypoint backup = Waypoints.top();
        Waypoints.pop();

        //  If the node is less than the sight distance, and we can see it without problems, the go directly to that Waypoint
        if( gg::FastDIST(cTransform->getPosition(), Waypoints.top().Position) > SightDistance ||
            world->DoesItHitSomething(cTransform->getPosition() + gg::Vector3f(0, 10, 0), Waypoints.top().Position + gg::Vector3f(0, 10, 0))
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

void CNavmeshAgent::CheckForSideCollisions(gg::Vector3f DirVector){
    gg::Vector2f Right(DirVector.X, DirVector.Z);

    Right = gg::Vector2f(Right.Y, -Right.X);
    gg::Vector2f Left = Right * -1;

    RS = cTransform->getPosition() + gg::Vector3f((Size.X+5)*Right.X, 5, (Size.Z+5)*Right.Y);
    LS = cTransform->getPosition() + gg::Vector3f((Size.X+5)*Left.X,  5, (Size.Z+5)*Left.Y);

    gg::Vector3f Increment(DirVector.X*50, 0, DirVector.Z*50);
    if(world->DoesItHitSomething(RS, RS + Increment)){
        gg::cout("Apply force to Left", gg::Color(102, 0, 102));
        cRigidBody->applyCentralForce(gg::Vector3f(Left.X, 0, Left.Y)*FORCE_FACTOR*1.2);
        
        //  Debug
        if(Singleton<Pathfinding>::Instance()->isDisplayVectorsEnabled())
            Engine->Draw3DLine(cTransform->getPosition(), cTransform->getPosition() + gg::Vector3f(Left.X, 0, Left.Y)*50, gg::Color(102, 0, 102), 5);
    }
    if(world->DoesItHitSomething(LS, LS + Increment)){
        gg::cout("Apply force to Right", gg::Color(102, 0, 102));
        cRigidBody->applyCentralForce(gg::Vector3f(Right.X, 0, Right.Y)*FORCE_FACTOR*1.2);

        //  Debug
        if(Singleton<Pathfinding>::Instance()->isDisplayVectorsEnabled())
            Engine->Draw3DLine(cTransform->getPosition(), cTransform->getPosition() + gg::Vector3f(Right.X, 0, Right.Y)*50, gg::Color(102, 0, 102), 5);
    }
}

void CNavmeshAgent::SetDestination(const gg::Vector3f &Target){
    Waypoints = std::stack<Waypoint>();
    Singleton<Pathfinding>::Instance()->FindPath(cTransform->getPosition(), Target, Waypoints);
    if(Waypoints.empty()){
        //gg::cout("No hay camino");
        currentlyMovingTowardsTarget = false;
        cRigidBody->setLinearVelocity(0.5);
        return;
    }
    Timer.Restart();
    currentlyMovingTowardsTarget = true;
}

bool CNavmeshAgent::HasDestination(){
    return currentlyMovingTowardsTarget;
}
