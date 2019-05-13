#include "Game.hpp"

//#include <iostream>
#include <cstdint>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"
#include "GameAI/AIDirector.hpp"

#include <Omicron/2D/Motor2D.hpp>

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include "BinaryParser.hpp"
#include <Omicron/Omicron.hpp>
#include <Omicron/2D/Motor2D.hpp>
#include <Bullet/ggDynWorld.hpp>
#include <Omicron/FX/Particle_System_DATA.hpp>
#include <GameAI/Pathfinding.hpp>

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

#include <Omicron/ZPlayer.hpp>

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

    soundSys = Singleton<SoundSystem>::Instance();
    //world->inito();
    //Engine->HideCursor(true);

}

Game::~Game(){
}

void Game::Init(){

    Engine->createZones(8);

    BinaryParser::ReadLoadZonesData("assets/BinaryFiles/LOADZONES.data");
    BinaryParser::ReadUnLoadZonesData("assets/BinaryFiles/UNLOADZONES.data");

    //Los eventos son propios de cada zona!
    BinaryParser::LoadBVHLevelData("assets/BinaryFiles/INICIO_MODELS.data", 1);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/INICIO_EVENTS.data", 1);
    //BinaryParser::LoadLevelData("assets/BinaryFiles/CALLE_PRINCIPAL.data", 4);
    //
    //

    //BinaryParser::LoadLevelData("assets/BinaryFiles/INICIO_MODELS.data", 1);
    //BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/INICIO_EVENTS.data", 1);
    //BinaryParser::LoadBVHLevelData("assets/BinaryFiles/INICIO_CIUDAD_MODELS.data", 4);
    //BinaryParser::LoadBVHLevelData("assets/BinaryFiles/CALLE_PRINCIPAL_MODELS.data", 5);
    //BinaryParser::LoadBVHLevelData("assets/BinaryFiles/CENTRO_MODELS.data", 6);
    //BinaryParser::LoadBVHLevelData("assets/BinaryFiles/FINAL_MODELS.data", 7);

    ///BinaryParser::LoadLevelData("assets/BinaryFiles/INICIO_CIUDAD_MODELS.data", 1);
    // BinaryParser::LoadLevelData("assets/BinaryFiles/CALLE_PRINCIPAL.data", 4);
    // BinaryParser::LoadSounds();
    // BinaryParser::ReadNatureData("assets/BinaryFiles/NATURE.data");

    Engine2D->InitHUD();


    cont->musicaJuegoPlay();
    cont->musicaJuegoPause(false);
    cont->musicaMenuStop();


    auto sF = Singleton<Factory>::Instance();
    Engine->crearCamara(90,0.15f,100.f, glm::vec3(2,2,10),glm::vec3(),16.f/9.f);
    luz = Engine->crearLuz(col,glm::vec3(5, 6, 0),glm::vec3(), Singleton<AssetManager>::Instance()->getShader("Default"));


    Engine->setPosition(luz, glm::vec3(125.964005, 10, -46.611977));

    // Pos init del heroe normal
    // 360, 0, 350
    Engine->HideCursor(true);

    uint16_t h = BinaryParser::ReadRespawnNodesData("assets/BinaryFiles/RESPAWN.data");
    // uint16_t h = sF->createHero(glm::vec3(0,30,10),-1);
    // uint16_t h = sF->createHero(glm::vec3(436.704,4.06207,-36.0146),-1);
    //
    // for (size_t i = 0; i < 50; i++) {
    // }
    // sF->createRusher(glm::vec3(0, 6, 0), 10);
    // sF->createRusher(glm::vec3(5,3,65),200);
    //
    MainCamera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, h));
    playerpos = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, h));
    // sF->createSoldierWandering(playerpos->getPosition(), 1000);

    Accumulator = 0;

    Singleton<Pathfinding>::Instance()->SetDebug(true);
    // world->setDebug(true);
    MasterClock.Restart();

    //sky.init();
    //Engine2D->prueba();

    // ParticleSystem_Data PS;
    // PS.Texture = "assets/Textures/boxtexure.jpeg";
    // PS.SpawnTime = 0.05;
    // PS.MaxParticles = 20;
    //
    // Engine->CreateParticleSystem(PS, 1);
    Director->init();
}

void Game::Update(){
    //CTransform* cTransform2 = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM,Manager->getHeroID()));
    ////std::cout << "POS BUENA:" <<cTransform2->getPosition()<< '\n';

    DeltaTime = MasterClock.Restart().Seconds();


    Engine->PollEvents();


    if(DeltaTime > 0.25) DeltaTime = 0.25;


    Accumulator += DeltaTime;

    // if(DeltaTime > 10000) throw std::exception();
    while(Accumulator >= 1/UPDATE_STEP){
        //Director->getposzona(1);
        // FIXED UPDATE//
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_PRESAVE));
        Manager->FixedUpdateAll();
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_POSTSAVE));
        //Director->comprobar();
        //Director->clipingEnemigos();
        world->stepSimulation(1/UPDATE_STEP*2.5, 10);
        Accumulator -= 1/UPDATE_STEP;
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

    glm::vec3 pos = playerpos->getPosition();
    // //std::cout << " - " << glm::to_string(pos) << '\n';
    pos.y += 10;
    Engine->setPosition(luz,pos);

    Engine->BeginDraw();
    Manager->UpdateAll();

    MainCamera->CameraUpdate();
    Engine->draw();
    //sky.Draw();

    // DEBUG PATHFINDING
    //glClear(GL_DEPTH_BUFFER_BIT);
    //Singleton<Pathfinding>::Instance()->DroNodes();

    Engine->DisplayFPS();
    Engine2D->DisplayHUD();

    // ======================= Debug =======================
     glClear(GL_DEPTH_BUFFER_BIT);
    // Engine->DrawZero();
    Manager->DibLineas();

    //Singleton<ggDynWorld>::Instance()->debugDrawWorld();
    // Director->DrawZones();
    // =====================================================


    Engine->EndDraw();
}

void Game::Resume(){
    Engine->HideCursor(true);
    Engine2D->InitHUD();
    MainCamera->resetMouse();

    cont->musicaJuegoPause(false);
    cont->musicaMenuStop();



    //Engine->HideCursor(true);
}


void Game::CLIN(){

    //Blackboard::ClearGlobalBlackboard();
    Manager->clin();
    world->clear();

    cont->musicaJuegoPause(true);
    cont->musicaMenuPlay();
    Engine->resetSceneGraph();
    //Engine2D->CLINNormal();
    //EventSystem->clin();

    // //std::cout << "1/60 = " << 1/60.F << '\n';
    // //std::cout << "UPDTES " << UPDATE  << '\n';
    // //std::cout << "DRO " << DRO  << '\n';

}
void Game::Pause(){
    cont->musicaJuegoPause(true);
}
