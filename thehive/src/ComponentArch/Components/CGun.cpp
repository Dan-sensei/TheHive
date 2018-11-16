#include "CGun.hpp"
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

#define VEL_FACTOR      9000.f
#define DIST_OFFSET     5.f

CGun::CGun()
:cTransform(nullptr)
{

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
        return;
    }

    total_bullets--;

    // // std::cout << "PIM!!! -> " << total_bullets << '\n';
    // Vector direccion normalizado, JUGADOR-TO
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

    // Crear una 'bala'
    uint8_t bullet = manager->createEntity();
    Material material("assets/Models/obradearte/prueba1.png");
    InitCRenderable_3D bModel("assets/Models/bullet.obj", material);
    InitCTransform bTransform(from.X,from.Y,from.Z, 0,0,0);
    InitCRigidBody bCollide(true,"assets/BoundingBoxes/bullet.bullet",  from.X,from.Y+DIST_OFFSET,from.Z, .5,.5,.5, 1, 0,0,0, 2);
    manager->addComponentToEntity(gg::TRANSFORM, bullet, &bTransform);
    manager->addComponentToEntity(gg::RENDERABLE_3D, bullet, &bModel);
    manager->addComponentToEntity(gg::RIGID_BODY, bullet, &bCollide);

    CRigidBody* rb = static_cast<CRigidBody*>(manager->getComponent(gg::RIGID_BODY, bullet));
    vel.X *= VEL_FACTOR;
    vel.Y *= VEL_FACTOR;
    vel.Z *= VEL_FACTOR;
    rb->applyCentralForce(gg::Vector3f(vel.X,vel.Y,vel.Z));
}

int CGun::getBullets(){
    return total_bullets;
}

void CGun::initializeComponentData(const void* data){
    if(data){
        InitCGun* cData = (InitCGun*)data;

        total_bullets = cData->total_bullets;
        damage = cData->dmg;
        cadence = cData->cadence;
    }
    // Inicializar singletons
    engine = Singleton<GameEngine>::Instance();
    manager = Singleton<ObjectManager>::Instance();

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
