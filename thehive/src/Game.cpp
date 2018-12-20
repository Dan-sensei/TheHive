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

#define MOVEMENT_SPEED 1.f

#define FRAMERATE 60.f
#define UPDATE_STEP 15.f
#define BULLET_STEP 1.f/FRAMERATE

Game::Game(){
    Engine = Singleton<GameEngine>::Instance();

    //Engine->Starto();
    //Engine->HideCursor(true);

    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();
    Engine->HideCursor(true);
    UPDATE = 0;
    DRO = 0;
}

Game::~Game(){}

void Game::Init(){
    Singleton<ScreenConsole>::Instance()->InitHUD();

    auto _Factory = Singleton<Factory>::Instance();
    uint16_t key;

    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));


    uint16_t h = _Factory->createHero(gg::Vector3f(360, 200, 350),false);     //600
    MainCamera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, h));

    gg::Vector3f mapPos(0,0,0);
    uint16_t Dummy = _Factory->createPathFindingActor(gg::Vector3f(150, 83, 450));
    _Factory->LoadNavmeshTestMap1();

    world->setDebug(true);

    MasterClock.Restart();
}

void Game::Update(){
    Engine->BeginDro();
    DeltaTime = MasterClock.Restart().Seconds();

    //  SPIRAL OF DEATH. Not cool
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

    //  Interpolation tick!
    Tick = std::min(1.f, static_cast<float>( Accumulator/(1/UPDATE_STEP) ));
    Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE, &Tick));

    Manager->UpdateAll();

    MainCamera->CameraUpdate();

    Engine->Dro();
    Engine->DisplayFPS();

    Singleton<ggDynWorld>::Instance()->debugDrawWorld();
    Singleton<Pathfinding>::Instance()->DroNodes();
    Singleton<ScreenConsole>::Instance()->DisplayDebug();
    //Singleton<ScreenConsole>::Instance()->DisplayHUD();

    Engine->EndDro();
}

void Game::Resume(){

}

void Game::CLIN(){
    //Blackboard::ClearGlobalBlackboard();
    Manager->clin();// este esta bien creo
    world->clear();//clean es el vuestro// clear solo vacia los rigidbody sin quitar las fisicas
    //EventSystem->clin();
    //Singleton<ScreenConsole>::Instance()->CLIN();
    Singleton<ScreenConsole>::Instance()->CLINNormal();

    std::cout << "1/60 = " << 1/60.F << '\n';
    std::cout << "UPDTES " << UPDATE  << '\n';
    std::cout << "DRO " << DRO  << '\n';

}
