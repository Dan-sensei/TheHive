#include "CVida.hpp"
#include <cmath>

#include <GameAI/Pathfinding.hpp>
#include <cmath>
//#include <iostream>
#include <Omicron/2D/Motor2D.hpp>
#include <Singleton.hpp>
#include <GameAI/AIDirector.hpp>

#include <BT/Action.hpp>
#include <ComponentArch/Components/CPlayerController.hpp>
#include <ComponentArch/Components/CFlock.hpp>

//He cambiado la forma de recibir daño, he quitado el factor y directamente cada arma quita unos puntos de daño determinados.
//#define K_DMG_VALUE 20.f

CVida::CVida(int _vida)
:Manager(nullptr),vida(_vida),vida_max(_vida)
{
    Manager         = Singleton<ObjectManager>::Instance();
    hud             = Singleton<HUD>::Instance();
    triggerSystem   = Singleton<CTriggerSystem>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    s_muerte = new SonidoNormal();
    SS->createSound("event:/SFX/Jugador/PocaVida", s_muerte);

    s_muletillas = new SonidoNormal();
    SS->createSound("event:/Voces/Jugador/Muletillas", s_muletillas);

 }

CVida::~CVida() {

    delete s_muerte;
    delete s_muletillas;
}

void CVida::Muerte(){
    vida=0;
}
float CVida::getVida(){
    return vida;
}
bool CVida::quitarvida(const float &_factor){


    bool ret = false;
    vida -= _factor;
    //std::cout << "QUITANDO VIDA " <<_factor<< '\n';
    //std::cout << "QUITANDO VIDA " <<vida<< '\n';
    if(Manager->getComponent(gg::PLAYERCONTROLLER,getEntityID())){

        if(vida <= 0){
            vida=vida_max;
            Singleton<AIDirector>::Instance()->restart();
        }

        hud->setHealthBarPc(vida/vida_max);
        s_muerte->setParameter("Vida",vida);

        s_muerte->play();

        // if(vida<5){
        //   s_muerte->play();
      // }
    }
    else{
        if(vida <= 0){

            //sonido muletillas
            int ramstein=gg::genIntRandom(1, 8);
            if(ramstein==5){
                s_muletillas->play();
            }

            //gg::cout(" -- ENTITY["+std::to_string(getEntityID())+"] has died painfully");
            vida = 0;
            ret = true;

            //Manager->getComponent(gg::PLAYERCONTROLLER,Manager->getHeroID());
            //Manager->getComponent(gg::AIENEM,getEntityID());

            CAIEnem* cAIEnem = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,getEntityID()));
            CPlayerController* cPlayerController = static_cast<CPlayerController*>(Manager->getComponent(gg::PLAYERCONTROLLER,Manager->getHeroID()));
            //cTransform = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,yo->getEntityID()));
            switch (cAIEnem->getEnemyType()) {
                case gg::SOLDIER:
                    cPlayerController->currentsoldier--;
                    break;
                case gg::TANK:
                cPlayerController->currenttank--;
                    break;
                case gg::RUSHER:
                cPlayerController->currentrusher--;
                    break;
            }


            //
        }
    }
    //gg::cout("DAMAGE DONE-> "+std::to_string(K_DMG_VALUE*_factor)+"["+std::to_string(vida)+"/"+std::to_string(vida_max)+"]");

    return ret;
}

void CVida::Init(){
    cont=0;
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


void CVida::FixedUpdate() {
    if(Manager->getComponent(gg::PLAYERCONTROLLER,getEntityID())){
        cont++;
        if(cont>50){
            cont=0;
            vida++;
            if(vida>=vida_max){
                vida=vida_max;
            }
            hud->setHealthBarPc(vida/vida_max);
        }
    }
    else{
        if(vida <= 0){
            CTransform  *t  = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM,getEntityID()));
            CAIEnem     *AI = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,getEntityID()));
            if(t && AI){
                // //gg::cout("DEAD ALIEN");
                if(AI->getImAttacking())
                Action::aliensAttacking--;
                // Evento para que los enemigos vean que se ha muerto un aliado suyo

                triggerSystem->RegisterTriger(kTrig_DeadAlien,1,getEntityID(),t->getPosition(), 20, 5000, false, TData());
            }
            AIDirector* dir=Singleton<AIDirector>::Instance();
            dir->removeEnemy(t);
            CFlock* flock_lider = static_cast<CFlock*>(Manager->getComponent(gg::FLOCK,getEntityID()));
            if(flock_lider){
                flock_lider->Muerte();
            }
            Manager->removeEntity(getEntityID());
            //aqui se muere

        }

    }

}
