#include "Game.hpp"

//#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"
#include "GameAI/Pathfinding.hpp"
#include "GameAI/AIDirector.hpp"

#include <Omicron/2D/Motor2D.hpp>

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>
#include "BinaryParser.hpp"
#include <Omicron/Omicron.hpp>

#include <Omicron/2D/Motor2D.hpp>

#include <Bullet/ggDynWorld.hpp>
#include <Omicron/FX/Particle_System_DATA.hpp>


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

Game::Game()
:Accumulator(0)
{
    Engine = Singleton<Omicron>::Instance();
    Engine2D = Singleton<Motor2D>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    Director = Singleton<AIDirector>::Instance();
    cont = Singleton<GUIController>::Instance();

    //Engine->Starto();
    //Engine->HideCursor(true);

    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
<<<<<<< HEAD
    world->inito();

    soundSys = Singleton<SoundSystem>::Instance();
=======

    soundSys = Singleton<SoundSystem>::Instance();
    //world->inito();
    //Engine->HideCursor(true);
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce

}

Game::~Game(){
}

void Game::Init(){
    Engine->createZones(8);

    BinaryParser::ReadLoadZonesData("assets/BinaryFiles/LOADZONES.data");
    BinaryParser::ReadUnLoadZonesData("assets/BinaryFiles/UNLOADZONES.data");

    // Los eventos son propios de cada zona!
    BinaryParser::LoadLevelData("assets/BinaryFiles/INICIO.data", 1);
    // BinaryParser::LoadLevelData("assets/BinaryFiles/CALLE_PRINCIPAL.data", 4);


    //BinaryParser::LoadSounds();
    BinaryParser::ReadNatureData("assets/BinaryFiles/NATURE.data");



    Engine2D->InitHUD();


    cont->musicaJuegoPlay();
    cont->play_snap_game();
    cont->musicaMenuStop();


    auto sF = Singleton<Factory>::Instance();
<<<<<<< HEAD
    uint16_t key;

    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));


    // sF->createHero(gg::Vector3f(700, 100, 0),false);
    sF->createHero(gg::Vector3f(1760, 110, 350),false);     //600
    sF->createEnemy(gg::Vector3f(740, 100, 20));
    sF->createEnemy(gg::Vector3f(740, 100, 30));
    sF->createEnemy(gg::Vector3f(740, 100, 40));
    sF->createEnemy(gg::Vector3f(1760, 110, 390));
    sF->createEnemy(gg::Vector3f(1797, 120, 350));
    sF->createCollectableWeapon(gg::Vector3f(1797, 120, 330),2);

    gg::Vector3f mapPos(1400,120,0);
    sF->createCollisionableStaticModel(
        "assets/Models/CIUDAD/PROTOTIPO5/PROTOTIPO_CIUDAD.obj",
        "assets/Models/CIUDAD/PROTOTIPO5/PROTOTIPO_CIUDAD.bullet",
        "assets/Models/CIUDAD/PROTOTIPO5/PROTOTIPO_CIUDAD.png",
        mapPos
    );

    sF->createCollectableWeapon(gg::Vector3f(700, 100, 20),0);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 40),1);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 60),2);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 80),3);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 100),4);

    sF->createCollisionableDynamicModel(
        "assets/Models/cuboGrande.obj",
        "assets/BoundingBoxes/cuboGrande.bullet",
        "assets/Textures/e61.png",
        gg::Vector3f(mapPos.X+274, mapPos.Y, mapPos.Z+50));

    uint16_t idEx = sF->createCollisionableDynamicModel(
        "assets/Models/ModelsForEvents/door1.obj",
        "assets/Models/ModelsForEvents/door1.bullet",
        "assets/Textures/Domino.jpg",
        gg::Vector3f(mapPos.X+350, mapPos.Y-10, mapPos.Z+204));
    key = sF->createPickableItem(gg::Vector3f(1624, 120, 145));
    sF->createTouchableObject(gg::Vector3f(mapPos.X+345, mapPos.Y-13, mapPos.Z+215),idEx,gg::Vector3f(0,0.1,0),3200);

    idEx = sF->createCollisionableDynamicModel(
        "assets/Models/ModelsForEvents/door2.obj",
        "assets/Models/ModelsForEvents/door2.bullet",
        "assets/Textures/Domino.jpg",
        gg::Vector3f(mapPos.X+270.5, mapPos.Y-8, mapPos.Z+131));
        // i674,106,130
    sF->createTouchableObject(gg::Vector3f(mapPos.X+290, mapPos.Y-11, mapPos.Z+131),idEx,gg::Vector3f(0,-0.035,0),8000,key);

    ////////////////////////////////////////////////////////////////
    // TABLA MOLONA DE CONVERSION DE LA POSICION EN EL ESPACIO 3D //
    ////////////////////////////////////////////////////////////////
    //              X        Y       Z                            //
    // ---------------------------------------------------------- //
    // BELNDER  -> bX,      bY,     bZ                            //
    // JEUGO    -> jX-bX,   jY+bZ,  jZ-bY                         //
    ////////////////////////////////////////////////////////////////


    //factory->createCollisionableStaticModel("assets/Models/CIUDAD/PROTOTIPO_CIUDAD.obj", "assets/Models/CIUDAD/PROTOTIPO_CIUDAD.bullet", "assets/Models/CIUDAD/PROTOTIPO_CIUDAD.png", gg::Vector3f(700, 175, 0));
    uint16_t Dummy = sF->createPathFindingActor(gg::Vector3f(285, 0, 117));
    //factory->createStaticModel("assets/NavMeshes/L4D2Nav.obj", "assets/NavMeshes/L4D2Nav.png", gg::Vector3f(0, 0, 0));

    uint16_t Navmesh = Manager->createEntity();
    Material yelo("assets/NavMeshes/PROTOTIPO_CIUDAD.png");
    //Material yelo("assets/Textures/ice.bmp");

    CTransform* Transform = new CTransform(gg::Vector3f(0,80,0), gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Navmesh);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/NavMeshes/PROTOTIPO_CIUDAD.obj", yelo);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Navmesh);

    // uint16_t NavmeshGround = Manager->createEntity();
    // CRigidBody* RigidBody = new CRigidBody(false, false,"", 0, -10, 0, 680,10,800, 0, 0,0,0, 0.2);
    // Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, NavmeshGround);




    //
    // uint16_t Wall_1 = Manager->createEntity();
    // CRigidBody* RigidBody_1 = new CRigidBody(false, false,"", -280, 0, -100, 160, 100,265, 0, 0,0,0, 0.2f);
    // Manager->addComponentToEntity(RigidBody_1, gg::RIGID_BODY, Wall_1);
    //
    // uint16_t Wall_2 = Manager->createEntity();
    // CRigidBody* RigidBody_2 = new CRigidBody(false, false,"", -80, 0, 410, 215, 100,320, 0, 0,0,0, 0.2f);
    // Manager->addComponentToEntity(RigidBody_2, gg::RIGID_BODY, Wall_2);
    //
    // uint16_t Wall_3 = Manager->createEntity();
    // CRigidBody* RigidBody_3 = new CRigidBody(false, false,"", 110, 0, 70, 80, 100, 32, 0, 0,0,0, 0.2f);
    // Manager->addComponentToEntity(RigidBody_3, gg::RIGID_BODY, Wall_3);
    //
    // uint16_t Wall_4 = Manager->createEntity();
    // CRigidBody* RigidBody_4 = new CRigidBody(false, false,"", -25, 0, 17, 100, 125, 28, 0, 0,0,0, 0.2f);
    // Manager->addComponentToEntity(RigidBody_4, gg::RIGID_BODY, Wall_4);

    //60 -450
    //132 - 550

    CNavmeshAgent* Agent = static_cast<CNavmeshAgent*>(Manager->getComponent(gg::NAVMESHAGENT, Dummy));
    Agent->SetDestination(gg::Vector3f(280, -20, -377));


    // std::cout << "BEGIN GAME LOOP" << '\n';
    gg::cout("Testing", gg::Color(255, 0, 0, 1));

    Singleton<Pathfinding>::Instance()->SetDebug(true);
    while(Engine->isWindowOpen()) {

        world->stepSimulation(1.f / 11.f, 10.f);

        EventSystem->Update();

        Engine->BeginDro();
        Manager->sendMessageToAllEntities(gg::M_UPDATE);
        Engine->Dro();
        Engine->DisplayFPS();

        Singleton<ggDynWorld>::Instance()->debugDrawWorld();
        Singleton<Pathfinding>::Instance()->DroNodes();
        Singleton<ScreenConsole>::Instance()->DisplayDebug();

        Engine->EndDro();

        soundSys->update();
=======
    Engine->crearCamara(90,0.15f,300.f, glm::vec3(2,2,10),glm::vec3(),16.f/9.f);
    luz = Engine->crearLuz(col,glm::vec3(5, 6, 0),glm::vec3(), Singleton<AssetManager>::Instance()->getShader("Default"));


    Engine->setPosition(luz, glm::vec3(125.964005, 10, -46.611977));

    // Pos init del heroe normal
    // 360, 0, 350
    Engine->HideCursor(true);

    uint16_t h = BinaryParser::ReadRespawnNodesData("assets/BinaryFiles/RESPAWN.data");
    // uint16_t h = sF->createHero(glm::vec3(0,30,10),-1);
    // uint16_t h = sF->createHero(glm::vec3(436.704,4.06207,-36.0146),-1);

    //for (size_t i = 0; i < 50; i++) {
    //}
    //sF->createRusher(glm::vec3(0, 6, 0), 10);
    //sF->createRusher(glm::vec3(5,3,65),200);


    // Director->init();   // IADIRECTOR

    MainCamera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, h));
    playerpos = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, h));
    //sF->createSoldierWandering(playerpos->getPosition(), 1000);


    // uint16_t n = Manager->createEntity();
    // CStaticModel* m = new CStaticModel("assets/BinaryFiles/BinaryModels/NavmeshCITY.modelgg", AssetManager::getMaterial("Nav"), glm::vec3(0,3,0), glm::vec3());
    // Manager->addComponentToEntity(m,gg::STATICMODEL,n);


    Accumulator = 0;

    //Singleton<Pathfinding>::Instance()->SetDebug(true);
    // world->setDebug(true);
    MasterClock.Restart();
    Engine2D->InitHUD();

    sky.init();
    //Engine2D->prueba();
    // //std::cout << "\n -- INIT -- " << '\n';

    ParticleSystem_Data PS;
    PS.Texture = "assets/Textures/Particles/BlueQuad.png";
    PS.SpawnTime = 0.05;
    PS.MaxParticles = 20;

    Engine->CreateParticleSystem(PS, 1);
}

void Game::Update(){
    //CTransform* cTransform2 = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM,Manager->getHeroID()));
    ////std::cout << "POS BUENA:" <<cTransform2->getPosition()<< '\n';

    DeltaTime = MasterClock.Restart().Seconds();

    // //std::cout << " - POLL EVENTS" << '\n';
    Engine->PollEvents();


    if(DeltaTime > 0.25) DeltaTime = 0.25;

    // //std::cout << " - WHILE" << '\n';
    Accumulator += DeltaTime;

    // //std::cout << "  - Delta time1 : " << DeltaTime << '\n';
    // if(DeltaTime > 10000) throw std::exception();
    while(Accumulator >= 1/UPDATE_STEP){
        // FIXED UPDATE//
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_PRESAVE));
        Manager->FixedUpdateAll();
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_POSTSAVE));
        //Director->comprobar();
        //Director->clipingEnemigos();
        world->stepSimulation(1/UPDATE_STEP*2.5, 10);
        Accumulator -= 1/UPDATE_STEP;
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
    }

    // //std::cout << " - EVENTSYSTEM UPDATE" << '\n';
    EventSystem->Update();

    //Director->update(DeltaTime);


    soundSys->update();
    //Director->update(DeltaTime);
    //Director->clipingEnemigos();

    //  Interpolation tick!
    Tick = std::min(1.f, static_cast<float>( Accumulator/(1/UPDATE_STEP) ));
    Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE, &Tick));
    // glm::vec3 pos = playerpos->getPosition();
    // std::cout << " - " << glm::to_string(pos) << '\n';
    // pos.y = 15;
    // //std::cout << " - BEGIN DRAW" << '\n';
    Engine->BeginDraw();

    // //std::cout << "  - UPDATE ALL" << '\n';
    Manager->UpdateAll();

    ////std::cout << "Update" << '\n';
    MainCamera->CameraUpdate();
    //Engine->print();

    // //std::cout << "  - DRAW" << '\n';
    Engine->draw();
    //sky.Draw();

    Engine->DisplayFPS();

    Engine2D->DisplayHUD();

    // Consola por pantalla
    // Singleton<ggDynWorld>::Instance()->debugDrawWorld();
    //Singleton<Pathfinding>::Instance()->DroNodes();

    // //std::cout << " - END DRAW" << '\n';
    Engine->EndDraw();

}

void Game::Resume(){
    Engine->HideCursor(true);
    Engine2D->InitHUD();
    MainCamera->resetMouse();

    cont->musicaJuegoPause(false);
    cont->musicaMenuStop();
    cont->play_snap_game();
    Engine2D->pauseVida(false);



    //Engine->HideCursor(true);
}


void Game::CLIN(){

    //Blackboard::ClearGlobalBlackboard();
    Manager->clin();
<<<<<<< HEAD
    Engine->clean();
    world->clean();
    EventSystem->clin();
    soundSys->CLIN();
=======
    world->clear();

    cont->musicaJuegoStop();
    cont->musicaMenuPlay();
    cont->play_snap_menu();
    Engine2D->stopVida();

    //Engine2D->CLINNormal();
    //EventSystem->clin();

    // //std::cout << "1/60 = " << 1/60.F << '\n';
    // //std::cout << "UPDTES " << UPDATE  << '\n';
    // //std::cout << "DRO " << DRO  << '\n';

}
void Game::Pause(){
    cont->musicaJuegoPause(true);
    cont->play_snap_menu();
    Engine2D->pauseVida(true);

>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
}
