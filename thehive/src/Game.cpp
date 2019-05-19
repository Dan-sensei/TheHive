#include "Game.hpp"

//#include <iostream>
#include <cstdint>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"
#include "GameAI/AIDirector.hpp"

#include <Omicron/2D/Motor2D.hpp>

#include "PopState.hpp"
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
    CLIN();
}

void Game::Init(){
    Singleton<AssetManager>::Instance()->loadInit();
    Engine->resizeFrameBuffers(1280, 720);

    Engine->createZones(8);

    BinaryParser::ReadLoadZonesData("assets/BinaryFiles/LOADZONES.data");
    BinaryParser::ReadUnLoadZonesData("assets/BinaryFiles/UNLOADZONES.data");

    //Los eventos son propios de cada zona!
    BinaryParser::LoadBVHLevelData("assets/BinaryFiles/INICIO_MODELS.data", 1);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/INICIO_EVENTS.data", 1);

    Engine2D->InitHUD();


    cont->musicaJuegoPlay();
    cont->musicaJuegoPause(false);
    cont->musicaMenuStop();


    auto sF = Singleton<Factory>::Instance();
    Engine->crearCamara(90,0.15f,100.f, glm::vec3(2,2,10),glm::vec3(),16.f/9.f);
    luz = Engine->crearLuz(col,glm::vec3(5, 6, 0),glm::vec3(), Singleton<AssetManager>::Instance()->getShader("Default"));


    glm::vec3 tmp(-19,-21,22);
    sF->createTank(tmp,2000);

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

    // Singleton<Pathfinding>::Instance()->SetDebug(true);
    world->setDebug(true);
    MasterClock.Restart();

    //sky.init();
    //Engine2D->prueba();


    ParticleSystem_Data PS_D;
    PS_D.Texture = Singleton<AssetManager>::Instance()->getTexture("assets/Textures/Particles/Smoke.png");
    PS_D.SpawnTime = 0.25;
    PS_D.ParticleLifeTime = 3.5;
    PS_D.MaxParticles = 1/PS_D.SpawnTime * PS_D.ParticleLifeTime;

    BinaryParser::LoadParticleSystem(PS_D, "assets/BinaryFiles/ParticleTest.ps");
    PS = Engine->CreateParticleSystem(Singleton<Omicron>::Instance()->FORWARD_LAYER, PS_D);

    TData mes;
    mes.add(kDat_total_img,1);
    mes.add(kDat_img1,0);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(79.7904,-20.6495,59.8293), 5, 0, false, mes);
    TData mes1;
    mes1.add(kDat_total_img,1);
    mes1.add(kDat_img1,1);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(171.164,-23.4092,35.5667), 5, 0, false, mes1);
    TData mes2;
    mes2.add(kDat_total_img,1);
    mes2.add(kDat_img1,2);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(330.681,-42.8137,79.0592 ), 5, 0, false, mes2);

    //TData mes1;
    //mes1.add(kDat_total_img,1);
    //mes1.add(kDat_img1,3);
    //Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(81.9019,2.11054,41.7012), 5, 0, false, mes1);

    Director->init();


    auto estado = new PopState();
    estado->Addim(Singleton<AssetManager>::Instance()->getTexture("assets/HUD/asdw_esp.png"));
    estado->Addim(Singleton<AssetManager>::Instance()->getTexture("assets/HUD/camara_esp.png"));
    estado->Addim(Singleton<AssetManager>::Instance()->getTexture("assets/HUD/dash_esp.png"));
    Singleton<StateMachine>::Instance()->AddState(estado);
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
        // Director->getposzona(1);
        // FIXED UPDATE//
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_PRESAVE));
        Manager->FixedUpdateAll();
        Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE_POSTSAVE));

        // Director->comprobar();

        world->stepSimulation(1/UPDATE_STEP*2.5, 10);
        Accumulator -= 1/UPDATE_STEP;
    }

    // //std::cout << " - EVENTSYSTEM UPDATE" << '\n';
    EventSystem->Update();
    // Director->update(DeltaTime);

    //Director->update(DeltaTime);


    soundSys->update();
    //Director->update(DeltaTime);
    //Director->clipingEnemigos();

    //  Interpolation tick!
    Tick = std::min(1.f, static_cast<float>( Accumulator/(1/UPDATE_STEP) ));
    Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE, &Tick));

    glm::vec3 pos = playerpos->getPosition();
    // std::cout << " - " << glm::to_string(pos) << '\n';
    pos.y += 10;
    Engine->setPosition(luz,pos);

    pos.y -= 7;
    PS->setPosition(pos);

    Engine->BeginDraw();
    Manager->UpdateAll();


    MainCamera->CameraUpdate();
    Engine->draw();
    Engine->drawHUD();
    //sky.Draw();

    // DEBUG PATHFINDING
    //glClear(GL_DEPTH_BUFFER_BIT);
    //Singleton<Pathfinding>::Instance()->DroNodes();

    Engine->DisplayFPS();
    // Engine2D->DisplayHUD();

    // ======================= Debug =======================
     // glClear(GL_DEPTH_BUFFER_BIT);
    // Engine->DrawZero();
    // Manager->DibLineas();

    // Singleton<ggDynWorld>::Instance()->debugDrawWorld();
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
    Manager->clin();
    world->clear();

    cont->musicaJuegoPause(true);
    cont->musicaMenuPlay();
    Engine->resetSceneGraph();
}
void Game::Pause(){
    cont->musicaJuegoPause(true);
}
