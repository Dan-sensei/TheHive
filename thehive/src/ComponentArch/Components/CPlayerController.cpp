#include "CPlayerController.hpp"
#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <Util.hpp>

#define VEL_FACTOR      9000.f
#define MAX_ANGLE       12.f

#define ROTATE_KEY      gg::GG_LCONTROL
#define DASH_KEY        gg::GG_ALT
#define RUN_KEY         gg::GG_LSHIFT
#define JUMP_KEY        gg::GG_SPACEBAR
#define LCLICK          gg::GG_LCLICK

#define DASH_FACTOR     1.2f
#define RUN_FACTOR      1.1f
#define FORCE_FACTOR    7000.f

CPlayerController::CPlayerController()
:cTransform(nullptr)
{
  GranadeCreate=false;
}

CPlayerController::~CPlayerController() {

}

void CPlayerController::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_SETPTRS);

}

void CPlayerController::initializeComponentData(const void* data){
    //  We check if this entity has the TRANSFORM component
    engine = Singleton<GameEngine>::Instance();
    world = Singleton<ggDynWorld>::Instance();
    camera = static_cast<CCamera*>(Singleton<ObjectManager>::Instance()->getComponent(gg::CAMERA, getEntityID()));
    MHandler_SETPTRS();
    Manager = Singleton<ObjectManager>::Instance();

}


gg::EMessageStatus CPlayerController::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CPlayerController::MHandler_SETPTRS(){
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    cRigidBody = static_cast<CRigidBody*>(Singleton<ObjectManager>::Instance()->getComponent(gg::RIGID_BODY, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CPlayerController::MHandler_UPDATE(){

    if(!cTransform || !camera || !cRigidBody)  return gg::ST_ERROR;

    // -----------------------------------------------------------------------------
    // Echarle un vistazo!
    // CommonWindowInterface* window = m_guiHelper->getAppInterface()->m_window;
    // -----------------------------------------------------------------------------

    //  If exists, we get its position
    gg::Vector3f nextPosition = camera->getlastHeroPosition();
    bool heroRotation = true;

    // Vector direccion camara-heroe
    gg::Vector3f cV = camera->getCameraPositionBeforeLockRotation();
    gg::Vector3f cV2 = cV;
    gg::Vector3f hV = cRigidBody->getBodyPosition();
        cV.X -= hV.X;
        cV.Y -= hV.Y;
        cV.Z -= hV.Z;

    float length = sqrt(cV.X*cV.X + cV.Y*cV.Y + cV.Z*cV.Z);
        cV.X /= length;
        cV.Y /= length;
        cV.Z /= length;

    // Vector perpendicular al vector direccion
    gg::Vector3f ppV(-cV.Z,0,cV.X);

    // Vector que tendrá el impulso para aplicar al body
    gg::Vector3f force;

    if(engine->key(gg::GG_W)){
        force = gg::Vector3f(-cV.X,0,-cV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X-=cV.X;
        //     cV2.Z-=cV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // };
    }
    else if(engine->key(gg::GG_S)){
        force = gg::Vector3f(+cV.X,0,+cV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X+=cV.X;
        //     cV2.Z+=cV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // }
    }

    if(engine->key(gg::GG_A)){
        force = gg::Vector3f(-ppV.X,0,-ppV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X-=ppV.X;
        //     cV2.Z-=ppV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // };
    }
    else if(engine->key(gg::GG_D)){
        force = gg::Vector3f(+ppV.X,0,+ppV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X+=ppV.X;
        //     cV2.Z+=ppV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // }
    }
    if(engine->key(ROTATE_KEY))
        heroRotation = false;

    if(engine->key(DASH_KEY)){
        force.X *= 1.05;
        force.Z *= 1.05;
    }
    if(engine->key(RUN_KEY)){
        force.X *= 1.02;
        force.Z *= 1.02;
    }

    if(engine->key(JUMP_KEY)){
        force.Y = 6;
    }

    force.X *= FORCE_FACTOR;
    force.Y *= FORCE_FACTOR;
    force.Z *= FORCE_FACTOR;
    cRigidBody->applyCentralForce(force);

    // COPIA-PEGA DE LA DOCUMENTACION:
    // Bullet automatically deactivates dynamic rigid bodies, when the velocity is below a threshold for a given time.
    // Deactivated (sleeping) rigid bodies don't take any processing time, except a minor broadphase collision detection impact
    // (to allow active objects to activate/wake up sleeping objects)
    cRigidBody->activate(true);

    // And we update it accoding to the keyboard input
    camera->updateCameraTarget(cRigidBody->getBodyPosition(),heroRotation);

    // DISPARO -> NO VA EL CLICK IZQUIERDO =D
    gg::Vector3f ESTEVECTORNOSEUSAPARANADA = world->handleRayCast(camera->getCameraPosition(),camera->getCameraRotation());
    gg::Vector3f rayPos = world->handleRayCastWithoutCollision(camera->getCameraPosition(),camera->getCameraRotation());
    if(engine->key(gg::GG_E)){
        CGun* gun = static_cast<CGun*>(Singleton<ObjectManager>::Instance()->getComponent(gg::GUN, getEntityID()));
        if(gun){
            gun->shoot(rayPos);
        }

    }
    if(engine->key(gg::GG_G)&&GranadeCreate==false){
        gg::Vector3f gPos = cTransform->getPosition();
        gg::Vector3f from = gPos;
        gg::Vector3f to = world->handleRayCastWithoutCollision(camera->getCameraPosition(),camera->getCameraRotation());
        gg::Vector3f vel(
            to.X-from.X,
            to.Y-from.Y,
            to.Z-from.Z
        );

        float length = sqrt(vel.X*vel.X + vel.Y*vel.Y + vel.Z*vel.Z);
            vel.X /= length;
            vel.Y /= length;
            vel.Z /= length;

        uint16_t holyBomb = Manager->createEntity();
        Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
        InitCRenderable_3D CRenderableHolyBomb("assets/Models/Cube.obj", moradoDeLos80);
        InitCTransform CTransformHolyBomb(0,0,0, 0,0,0);
        InitCRigidBody CRigidBodyHolyBomb(false,"",  gPos.X,gPos.Y+10,gPos.Z, 1,1,1, 1, 0,0,0);
        Manager->addComponentToEntity(gg::TRANSFORM, holyBomb, &CTransformHolyBomb);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, holyBomb, &CRenderableHolyBomb);
        Manager->addComponentToEntity(gg::GRANADE, holyBomb);
        Manager->addComponentToEntity(gg::RIGID_BODY, holyBomb, &CRigidBodyHolyBomb);

        CRigidBody* rb = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, holyBomb));
        vel.X *= VEL_FACTOR;
        vel.Y *= VEL_FACTOR;
        vel.Z *= VEL_FACTOR;
        rb->applyCentralForce(gg::Vector3f(vel.X,vel.Y,vel.Z));

        GranadeCreate=true;
    }

    return gg::ST_TRUE;

}
