#include "CPlayerController.hpp"

#include <States/StateMachine.hpp>
#include <PauseState.hpp>
#include <IAState.hpp>
#include "CDynamicModel.hpp"
#include <AnimationLUT.hpp>
#include <ComponentArch/Components/CCamera.hpp>
#include <ComponentArch/Components/CHabilityController.hpp>
#include <ComponentArch/Components/CRigidBody.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>
#include <ComponentArch/Components/CGun.hpp>


#define GRENADE_VEL_FACTOR      500.f
#define GRENADE_THROW_Y_OFFSET  3.f

#define MAX_HERO_SPEED      2

#define ROTATE_KEY          gg::LCONTROL
#define DASH_KEY            gg::H
#define RUN_KEY             gg::LSHIFT
#define JUMP_KEY            gg::SPACEBAR
#define RELOAD_KEY          gg::R
#define WEAPON_KEY          gg::Q

#define FORCE_FACTOR        500.f
#define JUMP_FORCE_FACTOR   FORCE_FACTOR*6.2f
#define DASH_FORCE_FACTOR   FORCE_FACTOR/35.f

#define MULT_RUN_FACTOR     1.5
#define MULT_DASH_FACTOR    3
//int CPlayerController::cont_enemigos=2;

CPlayerController::CPlayerController()
:Engine(nullptr), Manager(nullptr), world(nullptr), cTransform(nullptr), cRigidBody(nullptr), camera(nullptr),hab(nullptr)//,hab(0,2000,4000)
,ToggleFreeCameraKey(true), FreeCamera(false), PlayerMovement(true), cV(0,0,1)
{

}

CPlayerController::~CPlayerController() {
    if(secondWeapon) delete secondWeapon;
    delete s_dash;
    //delete s_pasos;
}

void CPlayerController::Init(){
    //  We check if this entity has the TRANSFORM component
    Engine  = Singleton<Omicron>::Instance();
    world   = Singleton<ggDynWorld>::Instance();
    Manager = Singleton<ObjectManager>::Instance();
    factory = Singleton<Factory>::Instance();
    camera  = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, getEntityID()));
    MHandler_SETPTRS();

    pulsacion_f = false;
    debug1 = false;
    debug2 = false;
    MULT_BASE=1;

    maxsoldier  = 10;
    maxrusher   = 10;
    maxtank     = 10;

    currentsoldier = 1;
    currentrusher  = 1;
    currenttank    = 1;

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

    SS = Singleton<SoundSystem>::Instance();

    s_dash = new SonidoNormal();
    SS->createSound("event:/SFX/Jugador/Habilidades/Dash", s_dash);

    // s_pasos = new SonidoSuperficie();
    // SS->createSound("event:/SFX/Jugador/Pasos", s_pasos);

    KEYMAP[0] = {gg::_1, &CPlayerController::ToggleSkill1};
    KEYMAP[1] = {gg::_2, &CPlayerController::ToggleSkill2};
    KEYMAP[2] = {gg::_3, &CPlayerController::ToggleSkill3};
    KEYMAP[3] = {RELOAD_KEY, &CPlayerController::ReloadGun};
    KEYMAP[4] = {gg::G, &CPlayerController::ThrowGranade};
    KEYMAP[5] = {WEAPON_KEY, &CPlayerController::ChangeWeapon};
    KEYMAP[6] = {RUN_KEY, &CPlayerController::Run};
    KEYMAP[7] = {DASH_KEY, &CPlayerController::DASH};
    KEYMAP[8] = {JUMP_KEY, &CPlayerController::JUMP};
    KEYMAP[9] = {gg::P, &CPlayerController::TogglePause};

    KEYMAP[10] = {gg::I, &CPlayerController::invocasionwander};
    KEYMAP[11] = {gg::U, &CPlayerController::invocasionhorda};
    KEYMAP[12] = {gg::_4, &CPlayerController::ToggleFreeCamera};
    KEYMAP[13] = {gg::M, &CPlayerController::EnemyInfo};
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
    cDynamicModel = static_cast<CDynamicModel*>(Manager->getComponent(gg::DYNAMICMODEL, getEntityID()));
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

    //if(clocker.ElapsedTime().Seconds() < 0.1){
        //Engine->Draw3DLine(cTransform->getPosition() + glm::vec3(0, 0.5, 0), Target, gg::Color(255, 0, 0));
    //}
}

void CPlayerController::FixedUpdate(){

    if(!cTransform || !camera || !cRigidBody)  return;

    // Vector que tendrá el impulso para aplicar al body
    force.x = 0;
    force.y = 0;
    force.z = 0;
    MULT_FACTOR = 1;

    bool pressed = false;
    check_WASD(force, pressed);


    for(uint8_t i = 0; i < KEYMAP.size(); ++i){
        if(Engine->key(KEYMAP[i].KEY, true))  (this->*KEYMAP[i].Target)();
    }

    if(!PlayerMovement) return;

    if( !pressed ){
        if(cDynamicModel->getCurrentAnimation() != A_HERO::STANDING){
            cDynamicModel->ToggleAnimation(A_HERO::STANDING, 2);
        }
    }
    else{
        if(cDynamicModel->getCurrentAnimation() != A_HERO::WALKING){
            cDynamicModel->ToggleAnimation(A_HERO::WALKING, 0.3);
        }
    }


    glm::vec3 Direction = cRigidBody->getVirtualRotation() * glm::vec3(0,0,1);
    cRigidBody->setVirtualRotation(RotationBetween(Direction, cV));

    // Se aplican fuerzas       FORCE-----| |------------MAX_SPEED-------------| |------SOME_KEY_PRESSED?
    cRigidBody->applyConstantVelocity(force,MAX_HERO_SPEED*MULT_FACTOR*MULT_BASE,pressed);


    // DISPARO
    if(Engine->isLClickPressed()){
        // glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),cTransform->getPosition());
        Target = world->handleRayCast(camera->getCameraPosition(),camera->getTargetPosition());
        CGun* gun = static_cast<CGun*>(Manager->getComponent(gg::GUN, getEntityID()));
        clocker.Restart();
        if(gun) gun->shoot(Target);
    }

    // <DEBUG>
    //showDebug();
    // </DEBUG>
}

// Código de los tutoriales de OpengGL, a optimisar
glm::quat CPlayerController::RotationBetween(glm::vec3 &V1, glm::vec3 &V2){
	V1 = normalize(V1);
	V2 = normalize(V2);

	float cosTheta = dot(V1, V2);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = cross(glm::vec3(0.0f, 0.0f, 1.0f), V1);
		if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = cross(glm::vec3(1.0f, 0.0f, 0.0f), V1);

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = cross(V1, V2);

	float s = sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}

void CPlayerController::playerThrowHolyBomb(){

    glm::vec3 gPos   = cTransform->getPosition();
    glm::vec3 from   = gPos;
    glm::vec3 to     = world->getRaycastVector();
    glm::vec3 vel    = to-from;

    vel  = glm::normalize(vel);
    vel *= GRENADE_VEL_FACTOR/2;

    factory->createHolyBomb(glm::vec3(gPos.x,gPos.y+GRENADE_THROW_Y_OFFSET,gPos.z),vel);
}

void CPlayerController::playerThrowMatrioska(){
    glm::vec3 gPos   = cTransform->getPosition();
    glm::vec3 from   = gPos;
    glm::vec3 to     = world->getRaycastVector();
    glm::vec3 vel    = to-from;

    vel  = glm::normalize(vel);
    vel *= GRENADE_VEL_FACTOR/2;

    factory->createMatriuska(glm::vec3(gPos.x,gPos.y+GRENADE_THROW_Y_OFFSET,gPos.z),vel);
}

void CPlayerController::playerThrowDopple(){
    glm::vec3 gPos   = cTransform->getPosition();
    glm::vec3 from   = gPos;
    glm::vec3 to     = world->getRaycastVector();
    glm::vec3 vel    = to-from;

    vel  = glm::normalize(vel);
    vel *= GRENADE_VEL_FACTOR/2;

    factory->createSenyuelo(glm::vec3(gPos.x,gPos.y+GRENADE_THROW_Y_OFFSET,gPos.z),vel);
}

void CPlayerController::check_WASD(glm::vec3 &force, bool &flag_pressed){
    int8_t W_S = Engine->key(gg::S) - Engine->key(gg::W);
    int8_t A_D = Engine->key(gg::A) - Engine->key(gg::D);

    if(W_S || A_D){
        flag_pressed = true;

        camera->getDirectionVector(cV);

        if(W_S) force = glm::vec3(cV.x * W_S, 0, cV.z * W_S);

        // Vector perpendicular al vector direccion
        if(A_D) force += glm::vec3(-cV.z*A_D, 0, cV.x*A_D);

        force = glm::normalize(force);
    }
}

void CPlayerController::showDebug(){
    if(Engine->key(gg::F1)){
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
    Singleton<Motor2D>::Instance()->changeWeapon();
    if(isPrincipal){
        isPrincipal = false;

        Manager->removeComponentFromEntityMAP(gg::GUN,getEntityID());
        Manager->addComponentToEntity(secondWeapon,gg::GUN,getEntityID());

        secondWeapon->desenfundado();

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

        //secondWeapon->get
        secondWeapon->desenfundado();
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
    if(Engine->key(gg::F)){
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


void CPlayerController::ToggleSkill1(){
    hab->ToggleSkill(0);
}
void CPlayerController::ToggleSkill2(){
    hab->ToggleSkill(1);
}
void CPlayerController::ToggleSkill3(){
    hab->ToggleSkill(2);
}

void CPlayerController::ReloadGun(){
    CGun* gun = static_cast<CGun*>(Manager->getComponent(gg::GUN, getEntityID()));
    if(gun && gun->canReload() && !gun->isReloading()){
        Manager->returnIDFromRigid(nullptr);
        gun->reload();
    }
}

void CPlayerController::ThrowGranade(){
    // glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),cTransform->getPosition());
    glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),camera->getTargetPosition());
    ////std::cout << actualGrenadeState << '\n';
    (this->*mapFuncGrenades[actualGrenadeState])();
}

void CPlayerController::ChangeWeapon(){
    if(secondWeapon){
        CGun *aux = static_cast<CGun*>(Manager->getComponent(gg::GUN,getEntityID()));
        if(!aux->isReloading()){
            changeWeaponIfPossible(aux);
        }
    }
}

void CPlayerController::Run(){
    MULT_FACTOR = MULT_RUN_FACTOR;
}

void CPlayerController::DASH(){
    MULT_FACTOR = MULT_DASH_FACTOR;
    force.x *= DASH_FORCE_FACTOR;
    force.z *= DASH_FORCE_FACTOR;

    s_dash->play();
}

void CPlayerController::JUMP(){
    cRigidBody->applyCentralForce(glm::vec3(0, JUMP_FORCE_FACTOR, 0));
}
void CPlayerController::TogglePause(){
    Singleton<StateMachine>::Instance()->AddState(new PauseState(),false);
}

void CPlayerController::invocasionhorda(){
    auto hola=glm::vec3(651.342,0.684987,-14.1424);
    factory->createTank(hola, 200);
}
void CPlayerController::invocasionwander(){
    glm::vec3 hola[]={
        glm::vec3(463.316,0.684987,-23.9962),
        glm::vec3(496.804,0.684987,-21.1747),
        glm::vec3(443.705,0.684986,-26.6188),
        glm::vec3(454.321,0.684986,-18.0602),
        glm::vec3(514.321,0.684986,-20.0602),
        glm::vec3(520.321,0.684986,-25.0602),
        glm::vec3(603.705,0.684986,-20.6188),
        glm::vec3(553.705,0.684986,-18.6188)
    };
    //wandering
    for (int i = 0; i < 8; i++) {
        factory->createSoldierWandering(hola[i], 200);
    }
}
void CPlayerController::ToggleFreeCamera(){
    camera->ToogleFreeCamera();

    if(!FreeCamera){
        PlayerMovement = false;
        FreeCamera = true;
    }
    else{
        PlayerMovement = true;
        FreeCamera = false;
    }
}

void CPlayerController::EnemyInfo(){
    //devuelve ide de un objeto
    glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCast(camera->getCameraPosition(),camera->getTargetPosition(),200);
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