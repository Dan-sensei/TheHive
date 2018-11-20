#include "CPathfinding.hpp"
#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include "CTransform.hpp"

#include <GameAI/Pathfinding.hpp>
#include <cmath>

CPathfinding::CPathfinding()
:cTransform(nullptr)
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
        std::cout << "GENEEATING WAYPOINTS" << '\n';
        Singleton<Pathfinding>::Instance()->A_Estrella(6, Waypoints);
        std::cout << "Waypoints " << Waypoints.size() << '\n';
    }
    else{


        gg::Vector3f moveVector = gg::Vector3f(Waypoints.top().X - cTransform->getPosition().X, Waypoints.top().Y - cTransform->getPosition().Y,Waypoints.top().Z - cTransform->getPosition().Z);
        float modulo= sqrt(moveVector.X*moveVector.X + moveVector.Y*moveVector.Y + moveVector.Z*moveVector.Z);

        if(modulo <= SPEED){
            Waypoints.pop();
            return gg::ST_TRUE;
        }

        moveVector.X=(moveVector.X/modulo)*SPEED;
        moveVector.Y=(moveVector.Y/modulo)*SPEED;
        moveVector.Z=(moveVector.Z/modulo)*SPEED;

        gg::Vector3f nextPosition = gg::Vector3f(cTransform->getPosition().X+moveVector.X, cTransform->getPosition().Y+moveVector.Y, cTransform->getPosition().Z+moveVector.Z);
        cTransform->setPosition(nextPosition);

    }


    return gg::ST_TRUE;
}
