#include "CPlayerController.hpp"

#include <States/StateMachine.hpp>
#include <PauseState.hpp>
#include <IAState.hpp>


//#include <GameAI/Hability.hpp>
//#include <GameAI/Enumhabs.hpp>

// #include <GameEngine/Motor2D.hpp>

#define GRENADE_VEL_FACTOR      500.f
#define GRENADE_THROW_Y_OFFSET  3.f

#define MAX_HERO_SPEED      2

#define ROTATE_KEY          gg::GG_LCONTROL
#define DASH_KEY            gg::GG_ALT
#define RUN_KEY             gg::GG_LSHIFT
#define JUMP_KEY            gg::GG_SPACEBAR
#define RELOAD_KEY          gg::GG_R
#define WEAPON_KEY          gg::GG_Q

#define FORCE_FACTOR        500.f
#define JUMP_FORCE_FACTOR   FORCE_FACTOR*6.2f
#define DASH_FORCE_FACTOR   FORCE_FACTOR/35.f

#define MULT_RUN_FACTOR     1.5
#define MULT_DASH_FACTOR    3
//int CPlayerController::cont_enemigos=2;

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
    Engine  = Singleton<SurrealEngine>::Instance();
    world   = Singleton<ggDynWorld>::Instance();
    Manager = Singleton<ObjectManager>::Instance();
    factory = Singleton<Factory>::Instance();
    camera  = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, getEntityID()));
    MHandler_SETPTRS();


    pulsacion_soldier= false;
    pulsacion_tank= false;
    pulsacion_rusher= false;
    pulsacion_granada = false;
    pulsacion_espacio = false;
    pulsacion_q = false;
    pulsacion_dash = false;
    pulsacion_f = false;
    debug1 = false;
    debug2 = false;
    MULT_BASE=1;

    maxsoldier  =10;
    maxrusher   =10;
    maxtank     =10;

    currentsoldier=1;
    currentrusher=1;
    currenttank=1;

    //pulsacion_enemigos=false;


    // El heroe siempre empezara con un arma secundaria
    // Pistola por defecto
    isPrincipal = false;
    secondWeapon = nullptr;

    actualGrenadeState = 1;
    mapFuncGrenades.insert(std::make_pair(1,&CPlayerController::playerThrowHolyBomb));
    mapFuncGrenades.insert(std::make_pair(2,&CPlayerController::playerThrowMatrioska));
    mapFuncGrenades.insert(std::make_pair(3,&CPlayerController::playerThrowDopple));
    items.fill(0);
}


gg::EMessageStatus CPlayerController::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


// Message handler functions__________________________________________________________________
// |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CPlayerController::MHandler_SETPTRS(){
    cTransform = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, getEntityID()));
    cRigidBody = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, getEntityID()));
    // //std::cout << "llega" << '\n';
    hab = static_cast<CHabilityController*>(Manager->getComponent(gg::HAB, getEntityID()));
    //hab = static_cast<CHabilityController*>(Manager->getComponent(gg::HABILITY, getEntityID()));


    return gg::ST_TRUE;
}

void CPlayerController::Update(){
    int wheelState = Engine->getWheelState();
    if(wheelState!=0){
        actualGrenadeState -= wheelState;
        if(actualGrenadeState<1)    actualGrenadeState = 3;
        if(actualGrenadeState>3)    actualGrenadeState = 1;
        //gg::cout(" -- ACTUAL GRENADE SET: "+std::to_string(actualGrenadeState));
    }

    if(clocker.ElapsedTime().Seconds() < 0.1){
        //Engine->Draw3DLine(cTransform->getPosition() + glm::vec3(0, 0.5, 0), Target, gg::Color(255, 0, 0));
    }

}

void CPlayerController::FixedUpdate(){

    if(!cTransform || !camera || !cRigidBody)  return;
    //hab.update();
    // -----------------------------------------------------------------------------
    // Echarle un vistazo!
    // CommonWindowInterface* window = m_guiHelper->getAppInterface()->m_window;
    // -----------------------------------------------------------------------------

    //  If exists, we get its position

    bool heroRotation = true;

    camera->getDirectionVector(cV);
    cV  = glm::normalize(cV);

    // Vector perpendicular al vector direccion
    ppV = glm::vec3(-cV.z,0,cV.x);

    // Vector que tendrá el impulso para aplicar al body
    glm::vec3    force;
    bool            pressed = false;
    float           MULT_FACTOR = 1;

    if(Engine->key(gg::GG_1)){
        hab->ToggleSkill(0);
    }
    if(Engine->key(gg::GG_2)){
        hab->ToggleSkill(1);
    }
    if(Engine->key(gg::GG_3)){
        hab->ToggleSkill(2);
    }
    // if(Engine->key(gg::GG_T)){
    //     if(pulsacion_soldier==false){
    //         pulsacion_soldier=true;
    //         if(maxsoldier>currentsoldier){
    //             currentsoldier++;
    //             auto sF = Singleton<Factory>::Instance();
    //             sF->createSoldier(glm::vec3(-10,3, -50),200);
    //
    //         }
    //
    //     }
    // }
    // else{
    //     pulsacion_soldier= false;
    // }
    // if(Engine->key(gg::GG_Y)){
    //     if(pulsacion_tank==false){
    //         pulsacion_tank=true;
    //         if(maxtank>currenttank){
    //             currenttank++;
    //
    //             auto sF = Singleton<Factory>::Instance();
    //             sF->createTank(glm::vec3(5,3,65),200);
    //         }
    //     }
    // }
    // else{
    //     pulsacion_tank= false;
    // }
    // if(Engine->key(gg::GG_U)){
    //     if(pulsacion_rusher==false){
    //         pulsacion_rusher=true;
    //         if(maxrusher>currentrusher){
    //             currentrusher++;
    //
    //             auto sF = Singleton<Factory>::Instance();
    //             sF->createRusher(glm::vec3(-45,3,-23),200);
    //         }
    //     }
    // }
    // else{
    //     pulsacion_rusher= false;
    // }
    if(Engine->key(gg::GG_M)){
        //hab->ToggleSkill(2);
        //devuelve ide de un objeto
        glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(), cTransform->getPosition(),1000);
        int id=world->getIDFromRaycast();
        ////std::cout << "id:" <<id<< '\n';
        if(id!=-1){

            CAIEnem* AIEnem = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,id));
            if(AIEnem){
                ////std::cout << "no hay enemigo" << '\n';
                Singleton<StateMachine>::Instance()->AddState(new IAState(id),false);


            }
        }

        //gun->shoot(STOESUNUPDATE_PERODEVUELVEUNAPOSICION);
    }

    if(Engine->key(gg::GG_W))   W_IsPressed(force,pressed);
    if(Engine->key(gg::GG_A))   A_IsPressed(force,pressed);
    if(Engine->key(gg::GG_S))   S_IsPressed(force,pressed);
    if(Engine->key(gg::GG_D))   D_IsPressed(force,pressed);
    if(Engine->key(ROTATE_KEY)) heroRotation = false;

    if(Engine->key(RUN_KEY))    MULT_FACTOR = MULT_RUN_FACTOR;
    if(Engine->key(DASH_KEY)){
        if(!pulsacion_dash) {ApplyDash(force,MULT_FACTOR);}
    }
    else {pulsacion_dash = false;}

    if(Engine->key(JUMP_KEY)){
        if(!pulsacion_espacio /*&& abs(cRigidBody->getVelocity().y) < 40*/){
            pulsacion_espacio = true;
            cRigidBody->applyCentralForce(glm::vec3(0, JUMP_FORCE_FACTOR, 0));
        }
    }
    else{
        pulsacion_espacio = false;
    }

    // Se aplican fuerzas       FORCE-----| |------------MAX_SPEED-------------| |------SOME_KEY_PRESSED?
    cRigidBody->applyConstantVelocity(force,MAX_HERO_SPEED*MULT_FACTOR*MULT_BASE,pressed);

    // -----------------------------------
    // Acciones de Willy
    // -----------------------------------
    // DISPARO

    if(Engine->key(RELOAD_KEY)){
        CGun* gun = static_cast<CGun*>(Manager->getComponent(gg::GUN, getEntityID()));
        if(gun && !gun->getBullets() && !gun->isReloading()){
            Manager->returnIDFromRigid(nullptr);
            gun->reload();
        }
    }

    // DISPARO
    if(Engine->isLClickPressed()){
        // glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),cTransform->getPosition());
        Target = world->handleRayCast(camera->getCameraPosition(),camera->getTargetPosition());
        CGun* gun = static_cast<CGun*>(Manager->getComponent(gg::GUN, getEntityID()));
        clocker.Restart();
        if(gun) gun->shoot(Target);
    }

    if(Engine->key(WEAPON_KEY) && secondWeapon){
        CGun *aux = static_cast<CGun*>(Manager->getComponent(gg::GUN,getEntityID()));
        if(!pulsacion_q && !aux->isReloading()){
            changeWeaponIfPossible(aux);
        }
    }
    else{
        pulsacion_q = false;
    }

    // Graná
    if(Engine->key(gg::GG_G)){
        // glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),cTransform->getPosition());
        glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),camera->getTargetPosition());
        ////std::cout << actualGrenadeState << '\n';
        if(pulsacion_granada==false)
            (this->*mapFuncGrenades[actualGrenadeState])();
    }
    else{
        pulsacion_granada=false;
    }

    // <DEBUG>
    showDebug();
    // </DEBUG>

    if(Engine->key(gg::GG_P)) {
        //Engine->Close();
        Singleton<StateMachine>::Instance()->AddState(new PauseState(),false);

    }

}

void CPlayerController::playerThrowHolyBomb(){
    pulsacion_granada   = true;

    glm::vec3 gPos   = cTransform->getPosition();
    glm::vec3 from   = gPos;
    glm::vec3 to     = world->getRaycastVector();
    glm::vec3 vel    = to-from;

    vel  = glm::normalize(vel);
    vel *= GRENADE_VEL_FACTOR/2;

    factory->createHolyBomb(glm::vec3(gPos.x,gPos.y+GRENADE_THROW_Y_OFFSET,gPos.z),vel);
}

void CPlayerController::playerThrowMatrioska(){
    pulsacion_granada   = true;

    glm::vec3 gPos   = cTransform->getPosition();
    glm::vec3 from   = gPos;
    glm::vec3 to     = world->getRaycastVector();
    glm::vec3 vel    = to-from;

    vel  = glm::normalize(vel);
    vel *= GRENADE_VEL_FACTOR/2;

    factory->createMatriuska(glm::vec3(gPos.x,gPos.y+GRENADE_THROW_Y_OFFSET,gPos.z),vel);
}

void CPlayerController::playerThrowDopple(){
    pulsacion_granada   = true;

    glm::vec3 gPos   = cTransform->getPosition();
    glm::vec3 from   = gPos;
    glm::vec3 to     = world->getRaycastVector();
    glm::vec3 vel    = to-from;

    vel  = glm::normalize(vel);
    vel *= GRENADE_VEL_FACTOR/2;

    factory->createSenyuelo(glm::vec3(gPos.x,gPos.y+GRENADE_THROW_Y_OFFSET,gPos.z),vel);
}

void CPlayerController::W_IsPressed(glm::vec3 &force, bool &pressed){
    force = glm::vec3(-cV.x,0,-cV.z);
    // if(Engine->key(ROTATE_KEY)){
    //     cV2.x-=cV.x;
    //     cV2.z-=cV.z;
    //     camera->setCameraPositionBeforeLockRotation(cV2);
    // };
    pressed = true;
}

void CPlayerController::S_IsPressed(glm::vec3 &force, bool &pressed){
    force = glm::vec3(+cV.x,0,+cV.z);
    // if(Engine->key(ROTATE_KEY)){
    //     cV2.x+=cV.x;
    //     cV2.z+=cV.z;
    //     camera->setCameraPositionBeforeLockRotation(cV2);
    // }
    pressed = true;
}

void CPlayerController::D_IsPressed(glm::vec3 &force, bool &pressed){
    force = glm::vec3(-ppV.x,0,-ppV.z);
    // if(Engine->key(ROTATE_KEY)){
    //     cV2.x-=ppV.x;
    //     cV2.z-=ppV.z;
    //     camera->setCameraPositionBeforeLockRotation(cV2);
    // };
    pressed = true;
}

void CPlayerController::A_IsPressed(glm::vec3 &force, bool &pressed){
    force = glm::vec3(+ppV.x,0,+ppV.z);
    // if(Engine->key(ROTATE_KEY)){
    //     cV2.x-=ppV.x;
    //     cV2.z-=ppV.z;
    //     camera->setCameraPositionBeforeLockRotation(cV2);
    // };
    pressed = true;
}

void CPlayerController::ApplyDash(glm::vec3 &force,float &MULT_FACTOR){
    MULT_FACTOR = MULT_DASH_FACTOR;
    force.x *= DASH_FORCE_FACTOR;
    force.z *= DASH_FORCE_FACTOR;

    pulsacion_dash = true;
}

void CPlayerController::showDebug(){
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
        // gg::cout(
        //     "(X:"+std::to_string(cTransform->getPosition().x)+
        //     ",Y:"+std::to_string(cTransform->getPosition().y)+
        //     ",Z:"+std::to_string(cTransform->getPosition().z)+")"
        // );
    }
}

void CPlayerController::changeWeaponIfPossible(CGun *gun){
    Singleton<Motor2D>::Instance()->setbullet(1,gun->getBullets(),gun->getTotalBullets());
    pulsacion_q = true;
    Singleton<Motor2D>::Instance()->changeWeapon();
    if(isPrincipal){
        isPrincipal = false;

        Manager->removeComponentFromEntityMAP(gg::GUN,getEntityID());
        Manager->addComponentToEntity(secondWeapon,gg::GUN,getEntityID());

        //gg::cout("| -- PRINCIPAL TO SECONDARY -- ");
        //gg::cout("| -----> PRIMARY: "    +std::to_string(secondWeapon->getType()));
        secondWeapon = gun;
        //gg::cout("| -----> SECONDARY: "  +std::to_string(secondWeapon->getType()));
    }
    else{
        // SIEMPRE entrara primero aqui
        isPrincipal = true;

        Manager->removeComponentFromEntityMAP(gg::GUN,getEntityID());
        Manager->addComponentToEntity(secondWeapon,gg::GUN,getEntityID());

        //gg::cout("| -- SECONDARY TO PRINCIPAL -- ");
        //gg::cout("| -----> PRIMARY: "    +std::to_string(secondWeapon->getType()));
        secondWeapon = gun;
        //gg::cout("| -----> SECONDARY: "  +std::to_string(secondWeapon->getType()));
    }
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

void CPlayerController::SprintBuf(){
    MULT_BASE=2.5;
}

void CPlayerController::SprintDebuf(){
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
    return false;
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
