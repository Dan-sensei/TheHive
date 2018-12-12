#include "CVida.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>
#include <cmath>
#include <iostream>
#include <GameEngine/ScreenConsole.hpp>
#include <Singleton.hpp>

#define K_DMG_VALUE 20

CVida::CVida(int _vida)
:Manager(nullptr),vida(_vida),vida_max(_vida)
{
    Manager = Singleton<ObjectManager>::Instance();
}

CVida::~CVida() {}

bool CVida::quitarvida(const float &_factor){
    bool ret = false;

    // if(vida <= 0){
    //     ret = true;
    // }

    vida -= K_DMG_VALUE*_factor;
    if(vida <= 0){
        gg::cout(" -- ENTITY["+std::to_string(getEntityID())+"] has died painfully");
        vida = 0;
        ret = true;
    }
    gg::cout("DAMAGE DONE: ["+std::to_string(vida)+"/"+std::to_string(vida_max)+"]");

    // if(Manager->getComponent(gg::PLAYERCONTROLLER,getEntityID())){
    //     gg::cout("HEROE--");
    //     ret = false;
    // }

    // float res=(float)vida/vida_max;
    // Singleton<ScreenConsole>::Instance()->setvida(res);

    return ret;
}

void CVida::Init(){
    //  We check if this entity has the TRANSFORM component
    //Manager = Singleton<ObjectManager>::Instance();
    MHandler_SETPTRS();
}


gg::EMessageStatus CVida::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CVida::MHandler_SETPTRS(){
    //cRigidBody = static_cast<CRigidBody*>(Singleton<ObjectManager>::Instance()->getComponent(gg::RIGID_BODY, getEntityID()));
    //cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}


void CVida::Update() {

}
