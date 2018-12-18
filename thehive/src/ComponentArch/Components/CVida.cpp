#include "CVida.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>
#include <cmath>
#include <iostream>
#include <GameEngine/ScreenConsole.hpp>
#include <Singleton.hpp>

#include <BT/Action.hpp>

#define K_DMG_VALUE 20.f

CVida::CVida(int _vida)
:Manager(nullptr),vida(_vida),vida_max(_vida)
{
    Manager         = Singleton<ObjectManager>::Instance();
    hud             = Singleton<ScreenConsole>::Instance();
    triggerSystem   = Singleton<CTriggerSystem>::Instance();
}

CVida::~CVida() {}

bool CVida::quitarvida(const float &_factor){
    bool ret = false;

    vida -= K_DMG_VALUE*_factor;
    if(Manager->getComponent(gg::PLAYERCONTROLLER,getEntityID())){
        hud->setvida(vida/vida_max);
    }
    else{
        if(vida <= 0){
            gg::cout(" -- ENTITY["+std::to_string(getEntityID())+"] has died painfully");
            vida = 0;
            ret = true;
        }
    }
    gg::cout("DAMAGE DONE-> "+std::to_string(K_DMG_VALUE*_factor)+"["+std::to_string(vida)+"/"+std::to_string(vida_max)+"]");

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
    if(vida <= 0){
        if(!Manager->getComponent(gg::PLAYERCONTROLLER,getEntityID())){
            CTransform  *t  = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM,getEntityID()));
            CAIEnem     *AI = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,getEntityID()));
            if(t && AI){
                // gg::cout("DEAD ALIEN");
                if(AI->getImAttacking())
                    Action::aliensAttacking--;
                // Evento para que los enemigos vean que se ha muerto un aliado suyo
                triggerSystem->RegisterTriger(kTrig_DeadAlien,1,getEntityID(),t->getPosition(), 5, 5000, false, TData());
            }

            Manager->removeEntity(getEntityID());
        }
        else{
                //muerto
        }
    }
}
