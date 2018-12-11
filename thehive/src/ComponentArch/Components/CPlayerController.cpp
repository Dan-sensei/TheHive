#include "CPlayerController.hpp"
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <Util.hpp>
#include <string>
#include "Factory.hpp"
//#include <GameAI/Hability.hpp>
//#include <GameAI/Enumhabs.hpp>

// #include <GameEngine/ScreenConsole.hpp>

#define VEL_FACTOR          200.f
#define MAX_HERO_SPEED      3

#define ROTATE_KEY          gg::GG_LCONTROL
#define DASH_KEY            gg::GG_ALT
#define RUN_KEY             gg::GG_LSHIFT
#define JUMP_KEY            gg::GG_SPACEBAR
#define RELOAD_KEY          gg::GG_R
#define WEAPON_KEY          gg::GG_Q

#define FORCE_FACTOR        400.f
#define JUMP_FORCE_FACTOR   FORCE_FACTOR*15.f
#define DASH_FORCE_FACTOR   FORCE_FACTOR/25.f

#define MULT_RUN_FACTOR     1.5
#define MULT_DASH_FACTOR    3

CPlayerController::CPlayerController()
:Engine(nullptr), Manager(nullptr), world(nullptr), cTransform(nullptr), cRigidBody(nullptr), camera(nullptr),hab(nullptr)//,hab(0,2000,4000)
{
  GranadeCreate=false;
}

CPlayerController::~CPlayerController() {
    if(secondWeapon) delete secondWeapon;
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
    MULT_BASE=1;
    debug2 = false;

    // El heroe siempre empezara con un arma secundaria
    // Pistola por defecto
    isPrincipal = false;
    secondWeapon = nullptr;

    // Array de items con sus posiciones a -1
    // Ya que por ahora no tiene ningún item
}


gg::EMessageStatus CPlayerController::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


// Message handler functions__________________________________________________________________
// |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CPlayerController::MHandler_SETPTRS(){
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    cRigidBody = static_cast<CRigidBody*>(Singleton<ObjectManager>::Instance()->getComponent(gg::RIGID_BODY, getEntityID()));
    // std::cout << "llega" << '\n';
    hab = static_cast<CHabilityController*>(Singleton<ObjectManager>::Instance()->getComponent(gg::HAB, getEntityID()));
    //hab = static_cast<CHabilityController*>(Singleton<ObjectManager>::Instance()->getComponent(gg::HABILITY, getEntityID()));


    return gg::ST_TRUE;
}

void CPlayerController::FixedUpdate(){

    if(!cTransform || !camera || !cRigidBody)  return;
    //hab.update();
    // -----------------------------------------------------------------------------
    // Echarle un vistazo!
    // CommonWindowInterface* window = m_guiHelper->getAppInterface()->m_window;
    // -----------------------------------------------------------------------------

    //  If exists, we get its position
    gg::Vector3f nextPosition = camera->getlastHeroPosition();
    bool heroRotation = true;

    gg::Vector3f oPV = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA,getEntityID()))->getOffsetPositionVector();
    gg::Vector3f cV = camera->getCameraPositionBeforeLockRotation();
    gg::Vector3f hV = nextPosition;
    // gg::Vector3f cV2 = cV;  // cV2 POR AHORA no se usa para nada

    // cV es un vector direccion camara-heroe
    cV -= oPV;
    cV -= hV;
    cV  = gg::Normalice(cV);

    // Vector perpendicular al vector direccion
    gg::Vector3f ppV(-cV.Z,0,cV.X);

    // Vector que tendrá el impulso para aplicar al body
    gg::Vector3f    force;
    bool            pressed = false;

    float           MULT_FACTOR = 1;

    if(Engine->key(gg::GG_1)){
        hab->pulsado(0);
    }
    if(Engine->key(gg::GG_2)){
        hab->pulsado(1);
    }
    if(Engine->key(gg::GG_3)){
        hab->pulsado(2);
    }
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
        // gg::cout("RUN!");
        MULT_FACTOR = MULT_RUN_FACTOR;
    }
    if(Engine->key(DASH_KEY)){
        if(!pulsacion_dash){
            // gg::cout("DASH!");

            MULT_FACTOR = MULT_DASH_FACTOR;
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

    // Se aplican fuerzas
    float currentSpeed = gg::Modulo(cRigidBody->getXZVelocity());
    if(!pressed && currentSpeed == 0)
        goto continueProcessing;

    if(pressed && currentSpeed < ((MAX_HERO_SPEED*MULT_FACTOR)*MULT_BASE)) {    // If a key is pressed and we haven't reached max speed yet
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

    // And we update it accoding to the keyboard input

    // -----------------------------------
    // Acciones de Willy
    // -----------------------------------
    // DISPARO
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
            //CVida* vid = static_cast<CVida*>(Singleton<ObjectManager>::Instance()->getComponent(gg::VIDA, getEntityID()));
            //vid->quitarvida();
            //TData mes;
            //CTriggerSystem* EventSystem=Singleton<CTriggerSystem>::Instance();
            //EventSystem->PulsoTrigger(kTrig_Aturd,0,cTransform->getPosition(),500,mes);

            //hab.init();
            pulsacion_granada=true;
            gg::Vector3f gPos = cTransform->getPosition();
            gg::Vector3f from = gPos;
            gg::Vector3f to = world->getRaycastVector();

            gg::Vector3f vel=to-from;
            vel = gg::Normalice(vel);

            vel*= VEL_FACTOR/2;

            Singleton<Factory>::Instance()->createHolyBomb(
                gg::Vector3f(gPos.X,gPos.Y+5,gPos.Z),
                vel
            );
            //*/
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

    if(debug2){
        // DEBUG ACTIVATED
        gg::cout(
            "(X:"+std::to_string(cTransform->getPosition().X)+
            ",Y:"+std::to_string(cTransform->getPosition().Y)+
            ",Z:"+std::to_string(cTransform->getPosition().Z)+")"
        );
    }


    // </DEBUG>

    if(Engine->key(gg::GG_P)) Engine->Close();
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
void CPlayerController::buf(){
MULT_BASE=2.5;
}
void CPlayerController::debuf(){
MULT_BASE=1;
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

bool CPlayerController::hasItem(const uint16_t &_item){
    for(const uint16_t& i : items){
        if(i==_item){
            return true;
        }
    }
    return false;
}

bool CPlayerController::pickItem(const uint16_t &_item){
    // No compruebo duplicados entre items
    // Nunca pasara esa situacion
    for(const uint16_t &i : items){
        // gg::cout("items["+std::to_string(i)+"] = "+std::to_string(items[i]));
        if(i==0){
            items[i] = _item;
            return true;
        }
    }
    return false;
}

bool CPlayerController::useItem(const uint16_t &_item){
    for(const uint16_t &i : items){
        if(i==_item){
            items[i] = 0;
            return true;
        }
    }
    return false;
}
