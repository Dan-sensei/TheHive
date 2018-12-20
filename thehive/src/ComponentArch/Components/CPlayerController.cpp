#include "CPlayerController.hpp"

#include <States/StateMachine.hpp>
#include <PauseState.hpp>

#include <GameAI/Pathfinding.hpp>

//#include <GameAI/Hability.hpp>
//#include <GameAI/Enumhabs.hpp>

// #include <GameEngine/ScreenConsole.hpp>

#define VEL_FACTOR          2000.f
#define MAX_HERO_SPEED      6

#define ROTATE_KEY          gg::GG_LCONTROL
#define DASH_KEY            gg::GG_ALT
#define RUN_KEY             gg::GG_LSHIFT
#define JUMP_KEY            gg::GG_SPACEBAR
#define RELOAD_KEY          gg::GG_R
#define WEAPON_KEY          gg::GG_Q

#define FORCE_FACTOR        500.f
#define JUMP_FORCE_FACTOR   FORCE_FACTOR*6.f
#define DASH_FORCE_FACTOR   FORCE_FACTOR/50.f

#define MULT_RUN_FACTOR     1.5
#define MULT_DASH_FACTOR    3

CPlayerController::CPlayerController()
:Engine(nullptr), Manager(nullptr), world(nullptr), cTransform(nullptr), cRigidBody(nullptr), camera(nullptr)
{}

CPlayerController::~CPlayerController() {
}

void CPlayerController::Init(){
    //  We check if this entity has the TRANSFORM component
    Engine  = Singleton<GameEngine>::Instance();
    world   = Singleton<ggDynWorld>::Instance();
    Manager = Singleton<ObjectManager>::Instance();
    factory = Singleton<Factory>::Instance();
    camera  = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, getEntityID()));
    MHandler_SETPTRS();

    pulsacion_granada = false;
    pulsacion_q = false;
    pulsacion_dash = false;
    pulsacion_f = false;
    debug1 = false;
    debug2 = false;
    MULT_BASE=1;


    // El heroe siempre empezara con un arma secundaria
    // Pistola por defecto
    isPrincipal = false;

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
    // std::cout << "llega" << '\n';
    //hab = static_cast<CHabilityController*>(Manager->getComponent(gg::HABILITY, getEntityID()));


    return gg::ST_TRUE;
}

void CPlayerController::Update(){

    if(Engine->key(gg::GG_N))   {
        Singleton<Pathfinding>::Instance()->SwitchDisplayNodes();
        Engine->key(gg::GG_N)  = false;
        std::string Flag = Singleton<Pathfinding>::Instance()->isDisplayNodesEnabled() ? "TRUE" : "FALSE";
        gg::cout("Display Path: " + Flag, gg::Color(0, 102, 255, 1));
    }

    if(Engine->key(gg::GG_F))   {
        Singleton<Pathfinding>::Instance()->SwitchDisplayFacesNodes();
        Engine->key(gg::GG_F)  = false;
        std::string Flag = Singleton<Pathfinding>::Instance()->isDisplayFacesNodesEnabled() ? "TRUE" : "FALSE";
        gg::cout("Display Force Vectors: " + Flag, gg::Color(0, 102, 255, 1));
    }

    if(Engine->key(gg::GG_C))   {
        Singleton<Pathfinding>::Instance()->SwitchDisplayConnections();
        Engine->key(gg::GG_C)  = false;
        std::string Flag = Singleton<Pathfinding>::Instance()->isDisplayConnectionsEnabled() ? "TRUE" : "FALSE";
        gg::cout("Display Faces Nodes : " + Flag, gg::Color(0, 102, 255, 1));
    }

    if(Engine->key(gg::GG_P))   {
        Singleton<Pathfinding>::Instance()->SwitchDisplayPath();
        Engine->key(gg::GG_P)  = false;
        std::string Flag = Singleton<Pathfinding>::Instance()->isDisplayPathEnabled() ? "TRUE" : "FALSE";
        gg::cout("Display Connections: " + Flag, gg::Color(0, 102, 255, 1));
    }
    if(Engine->key(gg::GG_V))   {
        Singleton<Pathfinding>::Instance()->SwitchDisplayVectors();
        Engine->key(gg::GG_V)  = false;
        std::string Flag = Singleton<Pathfinding>::Instance()->isDisplayVectorsEnabled() ? "TRUE" : "FALSE";
        gg::cout("Display Nodes: " + Flag, gg::Color(0, 102, 255, 1));
    }

    if(Engine->key(gg::GG_I))   {   camera->SwitchInvertCamera(); Engine->key(gg::GG_I)  = false;    }

    gg::Vector3f Raycast;
    bool Hit = world->handleRayCast(camera->getCameraPosition(),camera->getCameraRotation(), Raycast);
    if(Hit) Engine->Draw3DLine(Raycast, Raycast+gg::Vector3f(0, 800, 0), gg::Color(255, 0, 0, 2));


    if(Engine->isLClickPressed() && Hit){
        Manager->sendMessageToAllEntities(Message(gg::M_NEW_POSITION, &Raycast));
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
    gg::Vector3f nextPosition = camera->getlastHeroPosition();
    bool heroRotation = true;

    gg::Vector3f oPV = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA,getEntityID()))->getOffsetPositionVector();
                 cV = camera->getCameraPositionBeforeLockRotation();
    gg::Vector3f hV = nextPosition;
    // gg::Vector3f cV2 = cV;  // cV2 POR AHORA no se usa para nada

    // cV es un vector direccion camara-heroe
    cV -= oPV;
    cV -= hV;
    cV  = gg::Normalice(cV);

    // Vector perpendicular al vector direccion
    ppV = gg::Vector3f(-cV.Z,0,cV.X);

    // Vector que tendrá el impulso para aplicar al body
    gg::Vector3f    force;
    bool            pressed = false;
    float           MULT_FACTOR = 5;

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

    if(Engine->key(JUMP_KEY))
        cRigidBody->moveUp();

    if(Engine->key(gg::GG_LCONTROL))
        cRigidBody->moveDown();



    // Se aplican fuerzas       FORCE-----| |------------MAX_SPEED-------------| |------SOME_KEY_PRESSED?
    cRigidBody->applyConstantVelocity(force,MAX_HERO_SPEED*MULT_FACTOR*MULT_BASE,pressed);

    // <DEBUG>
    showDebug();
    // </DEBUG>

    if(Engine->key(gg::GG_Q)) Engine->Close();
}

void CPlayerController::W_IsPressed(gg::Vector3f &force, bool &pressed){
    force = gg::Vector3f(-cV.X,0,-cV.Z);
    pressed = true;
}

void CPlayerController::S_IsPressed(gg::Vector3f &force, bool &pressed){
    force = gg::Vector3f(+cV.X,0,+cV.Z);
    pressed = true;
}

void CPlayerController::A_IsPressed(gg::Vector3f &force, bool &pressed){
    force = gg::Vector3f(-ppV.X,0,-ppV.Z);
    pressed = true;
}

void CPlayerController::D_IsPressed(gg::Vector3f &force, bool &pressed){
    force = gg::Vector3f(+ppV.X,0,+ppV.Z);
    pressed = true;
}

void CPlayerController::ApplyDash(gg::Vector3f &force,float &MULT_FACTOR){
    MULT_FACTOR = MULT_DASH_FACTOR;
    force.X *= DASH_FORCE_FACTOR;
    force.Z *= DASH_FORCE_FACTOR;

    pulsacion_dash = true;
}

void CPlayerController::showDebug(){
    if(Engine->key(gg::GG_F1)){
        if(!debug1){
            debug1 = true;
            debug2 = !debug2; //debug2 ? debug2=false : debug2=true;
            world->setDebug(debug2);
        }
    }
    else{
        debug1 = false;
    }

    // if(debug2){
    //     // DEBUG ACTIVATED
    //     gg::cout(
    //         "(X:"+std::to_string(cTransform->getPosition().X)+
    //         ",Y:"+std::to_string(cTransform->getPosition().Y)+
    //         ",Z:"+std::to_string(cTransform->getPosition().Z)+")"
    //     );
    // }
}
