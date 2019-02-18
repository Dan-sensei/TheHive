#include "CGun.hpp"

#define FORCE_FACTOR        1000.f
#define DIST_OFFSET         2.f

CGun::CGun(float _dmg, float _cadence, int _total_bullets, float _reloadDT, float _range, int _wType, std::string sonido_disparo, std::string sonido_recarga, std::string sonido_desenfundado)
:Engine(nullptr), Manager(nullptr), cTransform(nullptr),
damage(_dmg), cadence(_cadence), total_bullets(_total_bullets),
reloadDT(_reloadDT), range(_range), WEAPON_TYPE(_wType)
{
    ktotal_bullets = total_bullets;
    canShoot = true;
    reloading = false;

    SS = Singleton<SoundSystem>::Instance();
    s_disparo = SS->createSound(sonido_disparo);
    s_recarga = SS->createSound(sonido_recarga);
    s_desenfundado = SS->createSound(sonido_desenfundado);
}

CGun::~CGun() {

}

void CGun::shoot(gg::Vector3f to){
    CTriggerSystem* EventSystem=Singleton<CTriggerSystem>::Instance();
    if(canShoot && !reloading){
        // Activar cadencia
        canShoot = false;
        dtCadence = std::chrono::high_resolution_clock::now();

        // Comprobar balas
        if(!total_bullets){
            gg::cout("Click!");
            //EventSystem->PulsoTrigger(kTrig_EnemyNear,0,cTransform->getPosition(),500,TData());

            return;
        }

        //SONIDO DISPARO
        s_disparo->play();

        // Comprobar si no es la katana
        if(total_bullets!=-1){
            total_bullets--;
        }

        // Singleton<ScreenConsole>::Instance()->setbullet(0,total_bullets,ktotal_bullets);

        // Comprobar destino
        if(to.X == -1){
            gg::cout("PAM! - "+std::to_string(total_bullets));
            //SONIDO IMPACTO
            return;
        }

        gg::cout("PIM! - "+std::to_string(total_bullets));

        //TData mes;
        //CTriggerSystem* EventSystem=Singleton<CTriggerSystem>::Instance();
        //EventSystem->PulsoTrigger(kTrig_EnemyNear,0,cTransform->getPosition(),500,TData());

        // // std::cout << "PIM!!! -> " << total_bullets << '\n';
        gg::Vector3f from = cTransform->getPosition();

        gg::Vector3f vel=gg::Normalice(to-from);
        // Se modulara segun el danyo de cada arma 0-1
        vel *= FORCE_FACTOR*damage;


        Singleton<ggDynWorld>::Instance()->applyForceToRaycastCollisionBody(vel);
        float id =Singleton<ggDynWorld>::Instance()->getIDFromRaycast();
        //CTriggerSystem* EventSystem=Singleton<CTriggerSystem>::Instance();
        //EventSystem->PulsoTrigger(kTrig_Shoot,0,to,500,mes);//sonido de disparo
        /////////cambiar todo esto a una funcion de CAIENEM

        if(id!=-1){
            CAIEnem* AIEnem = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,id));
            if(AIEnem){
                AIEnem->setPlayerIsAttacking(true);
                //
                CVida *health = static_cast<CVida*>(Manager->getComponent(gg::VIDA,id));
                if(health){
                    gg::cout("PUM! -> ["+std::to_string(damage)+"]", gg::Color(0, 0, 255, 1));
                    health->quitarvida(damage);
                }
            }
        }

        // <DEBUG>
            // Factory *fac = Singleton<Factory>::Instance();
            // fac->createDebugBullet(gg::Vector3f(to));
        // </DEBUG>
    }
}

void CGun::reload(){
    // NEED TO APPLY THE RELOAD TIME
    gg::cout(" -- RELOAD -- ");
    reloading = true;
    dtReload = std::chrono::high_resolution_clock::now();
    s_recarga->play();
}

bool CGun::isReloading(){
    return reloading;
}

int CGun::getBullets(){
    return total_bullets;
}

int CGun::getTotalBullets(){
    return ktotal_bullets;
}

int CGun::getType(){
    return WEAPON_TYPE;
}

void CGun::Init(){
    // Inicializar singletons
    Engine = Singleton<GameEngine>::Instance();
    Manager = Singleton<ObjectManager>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}


gg::EMessageStatus CGun::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CGun::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    // Singleton<ScreenConsole>::Instance()->setbullet(0,total_bullets,ktotal_bullets);

    return gg::ST_TRUE;
}

void CGun::FixedUpdate(){
    // UPDATE
    if(reloading){
        auto end         = std::chrono::high_resolution_clock::now();
        auto elapsedtime = end - dtReload;
        auto ms          = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count();

        if(ms > reloadDT*1000){
            gg::cout(" -- RELOADED" , gg::Color(255, 0, 0, 1));
            reloading = false;
            total_bullets = ktotal_bullets;
        }
    }
    else if(!canShoot){
        auto end         = std::chrono::high_resolution_clock::now();
        auto elapsedtime = end - dtCadence;
        auto ms          = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count();

        if(ms > (1/cadence)*1000){
            // gg::cout(" --- READY TO SHOOT --- ", gg::Color(255, 0, 0, 1)),
            canShoot = true;
        }
    }
    Singleton<ScreenConsole>::Instance()->setbullet(0,total_bullets,ktotal_bullets);
}

void CGun::desenfundado(){
    s_desenfundado->play();
}
