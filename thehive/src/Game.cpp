#include "Game.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "GameEngine/Camera.hpp"
#include "Singleton.hpp"
#include "GameAI/Pathfinding.hpp"
#include "GameAI/NavmeshStructs.hpp"

#include "GameEngine/ScreenConsole.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>
#include "BinaryParser.hpp"
#include <SurrealEngine/TMotorTAG.hpp>

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
    Engine = Singleton<TMotorTAG>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();

    //Engine->Starto();
    //Engine->HideCursor(true);

    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();
    //Engine->HideCursor(true);
    UPDATE = 0;
    DRO = 0;
}

Game::~Game(){

}

void Game::Init(){
    //Singleton<ScreenConsole>::Instance()->InitHUD();
    BinaryParser::test();
    auto sF = Singleton<Factory>::Instance();
    Engine->crearCamara(90,0.1f,100.f, glm::vec3(7,5,10),glm::vec3(),16.f/9.f);

    Engine->print();
    // Pos init del heroe normal
    // 360, 0, 350
    uint16_t h = sF->createHero(glm::vec3(0,0,0),false);
    //sF->createRusher(glm::vec3(5,3,65),200);

    MainCamera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, h));

    // Material yelo("assets/Models/CIUDAD/Presentacion1/NAVMESH.png");
    //
    // uint16_t Navmesh = Manager->createEntity();
    // CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/Models/CIUDAD/Presentacion1/NAVMESH.obj", yelo);
    // Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Navmesh);

    Singleton<Pathfinding>::Instance()->SetDebug(false);
    world->setDebug(true);
    MasterClock.Restart();
}

void Game::Update(){
    DeltaTime = MasterClock.Restart().Seconds();

    Engine->PollEvents();

    if(DeltaTime > 0.25) DeltaTime = 0.25;

    Accumulator += DeltaTime;
    while(Accumulator >= 1/UPDATE_STEP){
        // FIXED UPDATE
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_PRESAVE));
        Manager->FixedUpdateAll();
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_POSTSAVE));
        world->stepSimulation(1/UPDATE_STEP*2.5, 10);
        Accumulator -= 1/UPDATE_STEP;
        ++UPDATE;
    }
    ++DRO;

    EventSystem->Update();

    //  Interpolation tick!
    Tick = std::min(1.f, static_cast<float>( Accumulator/(1/UPDATE_STEP) ));
    Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE, &Tick));

    Engine->BeginDraw();
    Manager->UpdateAll();

    //MainCamera->CameraUpdate();
    //Engine->print();

    Engine->draw();
    //Engine->DisplayFPS();

    // Consola por pantalla
    // Singleton<ScreenConsole>::Instance()->DisplayDebug();
    // Singleton<ScreenConsole>::Instance()->DisplayHUD();
    // Singleton<ggDynWorld>::Instance()->debugDrawWorld();
    // Singleton<Pathfinding>::Instance()->DroNodes();

    Engine->EndDraw();
}

void Game::Resume(){
    //Engine->HideCursor(true);
}

void Game::CLIN(){
    //Blackboard::ClearGlobalBlackboard();
    Manager->clin();// este esta bien creo
    world->clear();//clean es el vuestro// clear solo vacia los rigidbody sin quitar las fisicas
    //EventSystem->clin();
    //Singleton<ScreenConsole>::Instance()->CLIN();
    //Singleton<ScreenConsole>::Instance()->CLINNormal();

    // std::cout << "1/60 = " << 1/60.F << '\n';
    // std::cout << "UPDTES " << UPDATE  << '\n';
    // std::cout << "DRO " << DRO  << '\n';

}
