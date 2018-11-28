#include "CVida.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>
#include <cmath>
#include <iostream>

CVida::CVida(int _vida)
:Manager(nullptr),vida(_vida)
{

}

CVida::~CVida() {

}
void CVida::quitarvida(){
    vida--;
    if(vida==0){
        //destory
        //Manager->removeEntity(getEntityID());

    }
    std::cout << "vida:" <<vida << '\n';
}

void CVida::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::VIDA, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::VIDA, gg::M_SETPTRS);
}

void CVida::Init(){
    //  We check if this entity has the TRANSFORM component
    //Manager = Singleton<ObjectManager>::Instance();
    MHandler_SETPTRS();
}


gg::EMessageStatus CVida::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CVida::MHandler_SETPTRS(){
    //cRigidBody = static_cast<CRigidBody*>(Singleton<ObjectManager>::Instance()->getComponent(gg::RIGID_BODY, getEntityID()));
    //cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}


gg::EMessageStatus CVida::MHandler_UPDATE(){



    return gg::ST_TRUE;
}
