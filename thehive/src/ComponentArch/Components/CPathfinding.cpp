#include "CPathfinding.hpp"
#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include "CTransform.hpp"

#include <GameAI/Pathfinding.hpp>
#include <cmath>

CPathfinding::CPathfinding()
:cTransform(nullptr), currentWaypointID(0)
{

}

CPathfinding::~CPathfinding() {

}

void CPathfinding::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::PATHFINDING, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::PATHFINDING, gg::M_SETPTRS);
}

void CPathfinding::initializeComponentData(const void* data){
    //  We check if this entity has the TRANSFORM component
    engine = Singleton<GameEngine>::Instance();
    MHandler_SETPTRS();
}


gg::EMessageStatus CPathfinding::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CPathfinding::MHandler_SETPTRS(){
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

#define SPEED 1.f

gg::EMessageStatus CPathfinding::MHandler_UPDATE(){

    if(Waypoints.empty()){
        Singleton<Pathfinding>::Instance()->resetGraph();
        std::cout << "GENERATING WAYPOINTS" << '\n';
        uint16_t target = gg::genIntRandom(0, Singleton<Pathfinding>::Instance()->getGraphSize());
        std::cout << "CurrentWaypointID = " << currentWaypointID << " | Target = " << target << '\n';
        Singleton<Pathfinding>::Instance()->A_Estrella(currentWaypointID, target, Waypoints);
        std::cout << "Waypoints " << Waypoints.size() << '\n' << '\n';
        std::cout << "-----------------------------------------------" << '\n';
    }
    else{

        gg::Vector3f moveVector = Waypoints.top().Position - cTransform->getPosition();

        float modulo= gg::Modulo(moveVector);

        if(modulo <= 3) {
            currentWaypointID = Waypoints.top().ID;
            Waypoints.pop();
            return gg::ST_TRUE;
        }

        moveVector = (moveVector / modulo) * SPEED;


        gg::Vector3f nextPosition = cTransform->getPosition() + moveVector;
        cTransform->setPosition(nextPosition);

        if(Singleton<Pathfinding>::Instance()->isDebugging()){
            std::stack<Waypoint> debug = Waypoints;
            uint16_t color[4];
            color[0] = 1;
            color[1] = 10;
            color[2] = 255;
            color[3] = 200;

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

    }


    return gg::ST_TRUE;
}
