#include "CPlayerController.hpp"
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <Util.hpp>
#include <string>
#include "Factory.hpp"
// #include <GameEngine/ScreenConsole.hpp>

#define VEL_FACTOR          200.f
#define MAX_ANGLE           12.f
#define MAX_HERO_SPEED      5

#define ROTATE_KEY          gg::GG_LCONTROL
#define DASH_KEY            gg::GG_ALT
#define RUN_KEY             gg::GG_LSHIFT
#define JUMP_KEY            gg::GG_SPACEBAR
#define RELOAD_KEY          gg::GG_R
#define WEAPON_KEY          gg::GG_Q

#define DASH_FACTOR         1.2f
#define RUN_FACTOR          1.1f
#define FORCE_FACTOR        400.f
#define JUMP_FORCE_FACTOR   FORCE_FACTOR*20.f
#define DASH_FORCE_FACTOR   FORCE_FACTOR/9.f

CPlayerController::CPlayerController()
:Engine(nullptr), Manager(nullptr), world(nullptr), cTransform(nullptr), cRigidBody(nullptr), camera(nullptr)
{
  GranadeCreate=false;
}

CPlayerController::~CPlayerController() {
    if(secondWeapon) delete secondWeapon;
}

void CPlayerController::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::PLAYERCONTROLLER, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::PLAYERCONTROLLER, gg::M_SETPTRS);

}

void CPlayerController::Init(){
    //  We check if this entity has the TRANSFORM component
    Engine = Singleton<GameEngine>::Instance();
    world = Singleton<ggDynWorld>::Instance();
    camera = static_cast<CCamera*>(Singleton<ObjectManager>::Instance()->getComponent(gg::CAMERA, getEntityID()));
    MHandler_SETPTRS();
    Manager = Singleton<ObjectManager>::Instance();

    pulsacion_granada = false;
    pulsacion_espacio = false;
    pulsacion_q = false;
    pulsacion_dash = false;
    pulsacion_f = false;
    debug1 = false;
    debug2 = false;

    // El heroe siempre empezara con un arma secundaria
    // Pistola por defecto
    isPrincipal = false;
    secondWeapon = nullptr;
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
        cV-=hV;
        cV=gg::Normalice(cV);

    // Vector perpendicular al vector direccion
    gg::Vector3f ppV(-cV.Z,0,cV.X);

    // Vector que tendrá el impulso para aplicar al body
    gg::Vector3f    force;
    bool            pressed = false;
    float           MULT_FACTOR = 1;

    if(Engine->key(gg::GG_W)){
        force = gg::Vector3f(-cV.X,0,-cV.Z);
        // if(Engine->key(ROTATE_KEY)){
        //     cV2.X-=cV.X;
        //     cV2.Z-=cV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // };
        pressed = true;
    }
    else if(Engine->key(gg::GG_S)){
        force = gg::Vector3f(+cV.X,0,+cV.Z);
        // if(Engine->key(ROTATE_KEY)){
        //     cV2.X+=cV.X;
        //     cV2.Z+=cV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // }
        pressed = true;
    }

    if(Engine->key(gg::GG_A)){
        force = gg::Vector3f(-ppV.X,0,-ppV.Z);
        // if(Engine->key(ROTATE_KEY)){
        //     cV2.X-=ppV.X;
        //     cV2.Z-=ppV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // };
        pressed = true;
    }
    else if(Engine->key(gg::GG_D)){
        force = gg::Vector3f(+ppV.X,0,+ppV.Z);
        // if(Engine->key(ROTATE_KEY)){
        //     cV2.X+=ppV.X;
        //     cV2.Z+=ppV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // }
        pressed = true;
    }
    if(Engine->key(ROTATE_KEY))
        heroRotation = false;

    if(Engine->key(RUN_KEY)){
        gg::cout("RUN!");
        MULT_FACTOR = 3.5;
    }
    if(Engine->key(DASH_KEY)){
        if(!pulsacion_dash){
            gg::cout("DASH!");

            MULT_FACTOR = 6;
            force.X *= DASH_FORCE_FACTOR;
            force.Z *= DASH_FORCE_FACTOR;

            pulsacion_dash = true;
        }
    }
    else{
        pulsacion_dash = false;
    }

    if(Engine->key(JUMP_KEY)){
        if(!pulsacion_espacio && abs(cRigidBody->getVelocity().Y) < 40){
            pulsacion_espacio = true;
            cRigidBody->applyCentralForce(gg::Vector3f(0, JUMP_FORCE_FACTOR, 0));
        }
    }
    else{
        pulsacion_espacio = false;
    }

    // gg::cout(std::to_string(cRigidBody->getVelocity().Y));

    float currentSpeed = gg::Modulo(cRigidBody->getXZVelocity());
    if(!pressed && currentSpeed == 0)
        goto continueProcessing;

    if(pressed && currentSpeed < (MAX_HERO_SPEED*MULT_FACTOR)) {    // If a key is pressed and we haven't reached max speed yet
        force *= FORCE_FACTOR;
        cRigidBody->applyCentralForce(force);                       // Accelerate!
    }
    else if (currentSpeed > 2) {                                    // Any key is pressed, but the speed is higher than 2! We're moving
        force = cRigidBody->getVelocity() * gg::Vector3f(-0.08, 0, -0.08) * FORCE_FACTOR;
        cRigidBody->applyCentralForce(force);                       // Stopping!
    }
    else {                                                          // If we reach here, any key is pressed and the speed is below 2
        // Set it to 0
        cRigidBody->setLinearVelocity(gg::Vector3f(0, cRigidBody->getVelocity().Y, 0));
    }


    continueProcessing:
    // COPIA-PEGA DE LA DOCUMENTACION:
    // Bullet automatically deactivates dynamic rigid bodies, when the velocity is below a threshold for a given time.
    // Deactivated (sleeping) rigid bodies don't take any processing time, except a minor broadphase collision detection impact
    // (to allow active objects to activate/wake up sleeping objects)
    cRigidBody->activate(true);

    // And we update it accoding to the keyboard input
    camera->updateCameraTarget(cRigidBody->getBodyPosition(),heroRotation);

    // DISPARO -> NO VA EL CLICK IZQUIERDO =D
    gg::Vector3f STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),camera->getCameraRotation());
    gg::Vector3f rayPos = world->getRaycastVector();

    if(Engine->key(RELOAD_KEY)){
        CGun* gun = static_cast<CGun*>(Singleton<ObjectManager>::Instance()->getComponent(gg::GUN, getEntityID()));
        if(gun && !gun->getBullets() && !gun->isReloading()){
            gun->reload();
        }
    }
    // if(Engine->key(gg::GG_E)){
    if(Engine->isLClickPressed()){
        CGun* gun = static_cast<CGun*>(Singleton<ObjectManager>::Instance()->getComponent(gg::GUN, getEntityID()));
        if(gun){
            gun->shoot(STOESUNUPDATE_PERODEVUELVEUNAPOSICION);
        }
    }

    // Graná
    if(Engine->key(gg::GG_G) && GranadeCreate==false){
        if(pulsacion_granada==false){
            pulsacion_granada=true;
            gg::Vector3f gPos = cTransform->getPosition();
            gg::Vector3f from = gPos;
            gg::Vector3f to = world->getRaycastVector();

            gg::Vector3f vel=to-from;
            vel = gg::Normalice(vel);

            uint16_t holyBomb = Manager->createEntity();
            Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

            CTransform* Transform = new CTransform(gg::Vector3f(gPos.X,gPos.Y+10,gPos.Z), gg::Vector3f(0,0,0));
            Manager->addComponentToEntity(Transform, gg::TRANSFORM, holyBomb);

            CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/Cube.obj", moradoDeLos80);
            Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, holyBomb);

            CRigidBody* RigidBody = new CRigidBody(false,false,"", gPos.X,gPos.Y+10,gPos.Z, 1,1,1, 1, 0,0,0);
            Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, holyBomb);

            CGranade* Granade = new CGranade(FORCE_FACTOR*20,40,1);
            Manager->addComponentToEntity(Granade, gg::GRANADE, holyBomb);

            vel*= VEL_FACTOR/2;

            RigidBody->applyCentralForce(vel);

        }
        // GranadeCreate=true;
    }
    else{
        pulsacion_granada=false;
    }

    if(Engine->key(WEAPON_KEY) && secondWeapon){
        CGun *aux = static_cast<CGun*>(Manager->getComponent(gg::GUN,getEntityID()));
        if(!pulsacion_q && !aux->isReloading()){
            pulsacion_q = true;
            if(isPrincipal){
                isPrincipal = false;

                Manager->removeComponentFromEntityMAP(gg::GUN,getEntityID());
                Manager->addComponentToEntity(secondWeapon,gg::GUN,getEntityID());

                gg::cout("| -- PRINCIPAL TO SECONDARY -- ");
                gg::cout("| -----> PRIMARY: "    +std::to_string(secondWeapon->getType()));
                secondWeapon = aux;
                gg::cout("| -----> SECONDARY: "  +std::to_string(secondWeapon->getType()));
            }
            else{
                // SIEMPRE entrara primero aqui
                isPrincipal = true;

                Manager->removeComponentFromEntityMAP(gg::GUN,getEntityID());
                Manager->addComponentToEntity(secondWeapon,gg::GUN,getEntityID());

                gg::cout("| -- SECONDARY TO PRINCIPAL -- ");
                gg::cout("| -----> PRIMARY: "    +std::to_string(secondWeapon->getType()));
                secondWeapon = aux;
                gg::cout("| -----> SECONDARY: "  +std::to_string(secondWeapon->getType()));
            }

        }
    }
    else{
        pulsacion_q = false;
    }

    // <DEBUG>
    if(Engine->key(gg::GG_F1)){
        if(!debug1){
            debug1 = true;
            debug2? debug2=false : debug2=true;
            world->setDebug(debug2);
        }
    }
    else{
        debug1 = false;
    }
    // </DEBUG>

    // gg::cout(
    //     "(X:"+std::to_string(cTransform->getPosition().X)+
    //     ",Y:"+std::to_string(cTransform->getPosition().Y)+
    //     ",Z:"+std::to_string(cTransform->getPosition().Z)+")"
    // );

    return gg::ST_TRUE;

}

bool CPlayerController::heroHasSecondWeapon(){
    if(secondWeapon)    return true;
    else                return false;

}

int CPlayerController::setSecondWeapon(CGun *_weapon){
    int ret;
    if(secondWeapon){
        ret = secondWeapon->getType();
    }
    else{
        ret = -1;
    }
    secondWeapon = _weapon;
    return ret;
}

bool CPlayerController::canPickWeapon(){
    if(Engine->key(gg::GG_F)){
        if(!pulsacion_f){
            pulsacion_f = true;
            return true;
        }
    }
    else{
        pulsacion_f = false;
    }
    return true;
}
