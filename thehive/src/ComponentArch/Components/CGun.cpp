#include "CGun.hpp"

#define FORCE_FACTOR        200.f
#define DIST_OFFSET         5.f

CGun::CGun(float _dmg, float _cadence, int _total_bullets, float _reloadDT, float _range)
:Engine(nullptr), Manager(nullptr), cTransform(nullptr),
damage(_dmg), cadence(_cadence), total_bullets(_total_bullets),
reloadDT(_reloadDT), range(_range)
{
    ktotal_bullets = total_bullets;
}

CGun::~CGun() {

}

void CGun::initComponent() {
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto

    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::GUN, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::GUN, gg::M_SETPTRS);

}

void CGun::shoot(gg::Vector3f to){
    if(!total_bullets){
        gg::cout("Click!");
        return;
    }
    if(to.X == -1){
        total_bullets--;
        gg::cout("PAM! - "+std::to_string(total_bullets));
        return;
    }
    total_bullets--;

    gg::cout("PIM! - "+std::to_string(total_bullets));

    // // std::cout << "PIM!!! -> " << total_bullets << '\n';
    gg::Vector3f from = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,getEntityID()))->getPosition();
    gg::Vector3f vel(
        to.X-from.X,
        to.Y-from.Y,
        to.Z-from.Z
    );

    float length = sqrt(vel.X*vel.X + vel.Y*vel.Y + vel.Z*vel.Z);
        vel.X /= length;
        vel.Y /= length;
        vel.Z /= length;

    // Se modulara segun el danyo de cada arma 0-1
    vel.X *= FORCE_FACTOR;
    vel.Y *= FORCE_FACTOR;
    vel.Z *= FORCE_FACTOR;

    from.Y += DIST_OFFSET;
    Singleton<ggDynWorld>::Instance()->applyForceToRaycastCollisionBody(from,to,vel);
    Singleton<CTriggerSystem>::Instance()->PulsoTrigger(kTrig_EnemyNear,0,cTransform->getPosition(),2000,TData());
}

void CGun::reload(){
    // NEED TO APPLY THE RELOAD TIME
    gg::cout(" -- RELOAD -- ");
    total_bullets = ktotal_bullets;
}

int CGun::getBullets(){
    return total_bullets;
}

void CGun::Init(){

    // Inicializar singletons
    Engine = Singleton<GameEngine>::Instance();
    Manager = Singleton<ObjectManager>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}


gg::EMessageStatus CGun::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CGun::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CGun::MHandler_UPDATE(){
    // UPDATE

    // Update de las balas -> deberian desaparecer cuando choquen
    // FALTA EL DELETE DE LAS ENTIDADES (EJEM, DANI, EJEM)

    return gg::ST_TRUE;
}
