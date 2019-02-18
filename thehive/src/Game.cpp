#include "Game.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "GameEngine/Camera.hpp"
#include "Singleton.hpp"
#include "GameAI/Pathfinding.hpp"
#include "GameAI/AIDirector.hpp"
#include "GameAI/NavmeshStructs.hpp"

#include "GameEngine/ScreenConsole.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>

#define MOVEMENT_SPEED 1.f

#define FRAMERATE 60.f
#define UPDATE_STEP 15.f
#define BULLET_STEP 1.f/FRAMERATE

//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
/*
void printHexVal(uint16_t val) {
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
      }
   }
}
*/
//============================================================================================

Game::Game(){
    Engine = Singleton<GameEngine>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    Director = Singleton<AIDirector>::Instance();
    //Director = new AIDirector();

    //Engine->Starto();
    //Engine->HideCursor(true);

    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();



    Engine->HideCursor(true);
    UPDATE = 0;
    DRO = 0;
}

Game::~Game(){

}

void Game::Init(){
    Singleton<ScreenConsole>::Instance()->InitHUD();
    soundSys = Singleton<SoundSystem>::Instance();
    auto sF = Singleton<Factory>::Instance();
    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));

    // Pos init del heroe normal
    // 360, 0, 350
    //esto estar en ai director
    uint16_t h = sF->createHero(gg::Vector3f(10,3,65),false);
    //sF->createRusher(gg::Vector3f(5,3,65),200);
    //sF->createSwarm(gg::Vector3f(5,3,65),100);
    MainCamera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, h));

    sF->createCollectableWeapon(gg::Vector3f(20, 3, 50),2);

    //sF->createRusher(gg::Vector3f(-10,3, -50),200);
    //sF->createSoldierWandering(gg::Vector3f(-45,3,-23),200);

    gg::Vector3f mapPos(0,0,0);

    Director->init();

    /*
    // POR SI SE QUIERE CARGAR EL MAPA DE SIEMPRE
    uint16_t idEx = sF->createCollisionableDynamicModel(
        "assets/Models/ModelsForEvents/door1.obj",
        "assets/Models/ModelsForEvents/door1.bullet",
        "assets/Textures/Domino.jpg",
        gg::Vector3f(mapPos.X+-10, mapPos.Y+3, mapPos.Z+13)
    );
    sF->createTouchableObject(gg::Vector3f(mapPos.X+-15, mapPos.Y+1, mapPos.Z+18),idEx,gg::Vector3f(0,0.4,0),3200);


    idEx = sF->createCollisionableDynamicModel(
        "assets/Models/ModelsForEvents/door2.obj",
        "assets/Models/ModelsForEvents/door2.bullet",
        "assets/Textures/Domino.jpg",
        gg::Vector3f(mapPos.X+-40, mapPos.Y+5, mapPos.Z+-65)
    );
        // i674,106,130
    uint16_t key = sF->createPickableItem(gg::Vector3f(12, 10, -61));
    sF->createTouchableObject(gg::Vector3f(mapPos.X+-51, mapPos.Y+1, mapPos.Z+-60),idEx,gg::Vector3f(0,-0.035*4,0),8000,key);
    */

    sF->createStaticModel("assets/Models/CIUDAD/Presentacion1/GROUND.obj", "assets/Textures/Domino.jpg", gg::Vector3f());
    sF->createStaticModel("assets/Models/CIUDAD/Presentacion1/WALLS.obj", "assets/Textures/MetalPanelRectangular001_REFL_1K_SPECULAR.jpg", gg::Vector3f());
    sF->createStaticModel("assets/Models/CIUDAD/Presentacion1/CORNER.obj", "assets/Textures/DominoInverted.jpg", gg::Vector3f());
    sF->createStaticModel("assets/Models/CIUDAD/Presentacion1/CUBE.obj", "assets/Textures/DominoInverted.jpg", gg::Vector3f());
    sF->createStaticModel("assets/Models/CIUDAD/Presentacion1/PARKOUR.obj", "assets/Textures/DominoInverted.jpg", gg::Vector3f());
    sF->createStaticModel("assets/Models/CIUDAD/Presentacion1/PILAR.obj", "assets/Textures/DominoInverted.jpg", gg::Vector3f());

    //============================================================//
    // TABLA MOLONA DE CONVERSION DE LA POSICION EN EL ESPACIO 3D //
    //============================================================//
    //              X        Y       Z                            //
    // ---------------------------------------------------------- //
    // BELNDER  -> bX,      bY,     bZ                            //
    // JEUGO    -> jX-bX,   jY+bZ,  jZ-bY                         //
    //============================================================//

    uint16_t GROUND1 = Manager->createEntity();
    CRigidBody* RigidBody_1 = new CRigidBody(false, false,"", -8.61945, -27.88897, 2.74528, 44.103, 26.624, 71.781, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody_1, gg::RIGID_BODY, GROUND1);

    uint16_t GROUND2 = Manager->createEntity();
    CRigidBody* RigidBody_2 = new CRigidBody(false, false,"", -42.91862, -27.88897, -77.71061, 9.481, 26.624, 10.353, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody_2, gg::RIGID_BODY, GROUND2);

    {   // WALLS
        uint16_t WALL1 = Manager->createEntity();
        CRigidBody* Wall_1 = new CRigidBody(false, false,"", 34.01, 16.56, 2.5, 1.233, 19.709, 71.216, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Wall_1, gg::RIGID_BODY, WALL1);

        uint16_t WALL2 = Manager->createEntity();
        CRigidBody* Wall_2 = new CRigidBody(false, false,"", 17.03, 16.98, 11.15, 17.286, 20.453, 0.890, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Wall_2, gg::RIGID_BODY, WALL2);

        uint16_t WALL3 = Manager->createEntity();
        CRigidBody* Wall_3 = new CRigidBody(false, false,"", 9.188, 18.15, 73.13, 25.726, 20.103, 1, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Wall_3, gg::RIGID_BODY, WALL3);

        uint16_t WALL4 = Manager->createEntity();
        CRigidBody* Wall_4 = new CRigidBody(false, false,"", -15.57996, 17.31404, 41.9740, 0.780, 19.769, 31.333, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Wall_4, gg::RIGID_BODY, WALL4);

        uint16_t WALL5 = Manager->createEntity();
        CRigidBody* Wall_5 = new CRigidBody(false, false,"", -33.65699, 16.91, 11.63384, 18.820, 18.820, 1, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Wall_5, gg::RIGID_BODY, WALL5);

        uint16_t WALL6 = Manager->createEntity();
        CRigidBody* Wall_6 = new CRigidBody(false, false,"", -51.80, 14.84, -27.87, 1, 21.009, 41.047, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Wall_6, gg::RIGID_BODY, WALL6);

        uint16_t WALL7 = Manager->createEntity();
        CRigidBody* Wall_7 = new CRigidBody(false, false,"", 0.89903, 17.26899, -68.02306, 34.394, 19.340, 1, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Wall_7, gg::RIGID_BODY, WALL7);
    }

    {   // OBSTACLES
        uint16_t CUBE = Manager->createEntity();
        CRigidBody* Cube_ = new CRigidBody(false, false,"", -25.55783, 1.89, -31.38994, 6.4, 3.7, 7.4, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Cube_, gg::RIGID_BODY, CUBE);

        uint16_t PILAR = Manager->createEntity();
        CRigidBody* Pilar_ = new CRigidBody(false, false,"", 0.74, 8.35249, -13.28533, 2.020, 10.350, 2.620, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Pilar_, gg::RIGID_BODY, PILAR);

        uint16_t CORNER = Manager->createEntity();
        CRigidBody* Corner_ = new CRigidBody(false, false,"", -44.60902, 7.29961, 3.35913, 6.734, 8.963, 8.267, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Corner_, gg::RIGID_BODY, CORNER);
    }

    {   // PARKOUR
        uint16_t PLATFORM1 = Manager->createEntity();
        CRigidBody* Platform_1 = new CRigidBody(false, false,"", 21.85805, -0.75072, 7.40838, 3.951, 0.500, 2.755, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_1, gg::RIGID_BODY, PLATFORM1);

        uint16_t PLATFORM2 = Manager->createEntity();
        CRigidBody* Platform_2 = new CRigidBody(false, false,"", 29.52495, -0.19861, 7.40838, 3.776, 1.131, 2.755, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_2, gg::RIGID_BODY, PLATFORM2);

        uint16_t PLATFORM3 = Manager->createEntity();
        CRigidBody* Platform_3 = new CRigidBody(false, false,"", 29.52495, 0.60919, 0.88137, 3.776, 1.905, 3.743, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_3, gg::RIGID_BODY, PLATFORM3);

        uint16_t PLATFORM4 = Manager->createEntity();
        CRigidBody* Platform_4 = new CRigidBody(false, false,"", 29.52495, 1.18477, -8.79860, 3.776, 2.630, 4.131, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_4, gg::RIGID_BODY, PLATFORM4);

        uint16_t PLATFORM5 = Manager->createEntity();
        CRigidBody* Platform_5 = new CRigidBody(false, false,"", 29.52495, 1.65598, -18.92076, 3.776, 3.264, 4.219, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_5, gg::RIGID_BODY, PLATFORM5);

        uint16_t PLATFORM6 = Manager->createEntity();
        CRigidBody* Platform_6 = new CRigidBody(false, false,"", 29.52495, 1.97013, -28.88360, 3.776, 4.116, 4.219, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_6, gg::RIGID_BODY, PLATFORM6);

        uint16_t PLATFORM7 = Manager->createEntity();
        CRigidBody* Platform_7 = new CRigidBody(false, false,"", 29.52495, 2.61637, -37.54464, 3.776, 4.812, 3.064, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_7, gg::RIGID_BODY, PLATFORM7);

        uint16_t PLATFORM8 = Manager->createEntity();
        CRigidBody* Platform_8 = new CRigidBody(false, false,"", 29.52495, 7.69701, -55.00421, 3.986, 0.837, 12.126, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_8, gg::RIGID_BODY, PLATFORM8);

        uint16_t PLATFORM9 = Manager->createEntity();
        CRigidBody* Platform_9 = new CRigidBody(false, false,"", 16.44830, 7.69701, -62.12792, 9.073, 0.837, 5.040, 0, 0,0,0, 0.2);
        Manager->addComponentToEntity(Platform_9, gg::RIGID_BODY, PLATFORM9);

    }


    // Material yelo("assets/Models/CIUDAD/Presentacion1/NAVMESH.png");
    //
    // uint16_t Navmesh = Manager->createEntity();
    // CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/CIUDAD/Presentacion1/NAVMESH.obj", yelo);
    // Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Navmesh);

    Singleton<Pathfinding>::Instance()->SetDebug(false);
    MasterClock.Restart();
}

void Game::Update(){
    //CTransform* cTransform2 = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM,Manager->getHeroID()));
    //std::cout << "POS BUENA:" <<cTransform2->getPosition()<< '\n';

    DeltaTime = MasterClock.Restart().Seconds();

    if(DeltaTime > 0.25) DeltaTime = 0.25;

    Accumulator += DeltaTime;
    while(Accumulator >= 1/UPDATE_STEP){
        // FIXED UPDATE//
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_PRESAVE));
        Manager->FixedUpdateAll();
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_POSTSAVE));
        Director->comprobar();
        Director->clipingEnemigos();
        world->stepSimulation(1/UPDATE_STEP*2.5, 10);
        Accumulator -= 1/UPDATE_STEP;
        ++UPDATE;
    }
    ++DRO;

    EventSystem->Update();
    Director->update(DeltaTime);
    //Director->clipingEnemigos();
    //  Interpolation tick!
    Tick = std::min(1.f, static_cast<float>( Accumulator/(1/UPDATE_STEP) ));
    Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE, &Tick));

    Engine->BeginDro();
    Manager->UpdateAll();

    MainCamera->CameraUpdate();

    Engine->Dro();
    Engine->DisplayFPS();

    // Consola por pantalla
    Singleton<ScreenConsole>::Instance()->DisplayDebug();
    Singleton<ScreenConsole>::Instance()->DisplayHUD();
    // Singleton<ggDynWorld>::Instance()->debugDrawWorld();
    // Singleton<Pathfinding>::Instance()->DroNodes();

    Engine->EndDro();

    soundSys->update();
}

void Game::Resume(){
    Engine->HideCursor(true);
}

void Game::CLIN(){
    //Blackboard::ClearGlobalBlackboard();
    Manager->clin();// este esta bien creo
    world->clear();//clean es el vuestro// clear solo vacia los rigidbody sin quitar las fisicas
    //EventSystem->clin();
    //Singleton<ScreenConsole>::Instance()->CLIN();
    Singleton<ScreenConsole>::Instance()->CLINNormal();

    soundSys->CLIN();

    // std::cout << "1/60 = " << 1/60.F << '\n';
    // std::cout << "UPDTES " << UPDATE  << '\n';
    // std::cout << "DRO " << DRO  << '\n';

}
