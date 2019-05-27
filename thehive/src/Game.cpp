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


Game::Game()
:Accumulator(0)
{
    Engine = Singleton<Omicron>::Instance();
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

    Engine->createZones(7);

    BinaryParser::ReadLoadZonesData("assets/BinaryFiles/LOADZONES.data");
    BinaryParser::ReadUnLoadZonesData("assets/BinaryFiles/UNLOADZONES.data");

    //Los eventos son propios de cada zona!
    BinaryParser::LoadBVHLevelData("assets/BinaryFiles/INICIO_MODELS.data", 0);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/INICIO_EVENTS.data", 0);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/INICIO_LIGHTS.data", 0);

    BinaryParser::LoadLevelData("assets/BinaryFiles/PASILLOS_MODELS.data", 1);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/PASILLOS_EVENTS.data", 1);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/PASILLOS_LIGHTS.data", 1);

    BinaryParser::LoadLevelData("assets/BinaryFiles/TUNELES_MODELS.data", 2);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/TUNELES_EVENTS.data",2);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/TUNELES_LIGHTS.data", 2);

    BinaryParser::LoadBVHLevelData("assets/BinaryFiles/INICIO_CIUDAD_MODELS.data", 3);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/INICIO_CIUDAD_EVENTS.data",3);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/INICIO_CIUDAD_LIGHTS.data", 3);

    BinaryParser::LoadLevelData("assets/BinaryFiles/CALLE_PRINCIPAL_MODELS.data", 4);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/CALLE_PRINCIPAL_EVENTS.data",4);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/CALLE_PRINCIPAL_LIGHTS.data", 4);

    BinaryParser::LoadBVHLevelData("assets/BinaryFiles/CENTRO_MODELS.data", 5);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/CENTRO_EVENTS.data",5);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/CENTRO_LIGHTS.data", 5);
    //
    BinaryParser::LoadLevelData("assets/BinaryFiles/FINAL_MODELS.data", 6);
    BinaryParser::LoadLevelDataEvents("assets/BinaryFiles/FINAL_EVENTS.data",6);
    BinaryParser::LoadLevelLights("assets/BinaryFiles/FINAL_LIGHTS.data", 6);

    Engine->setLightsZone(0, true);
    Engine->ZONES[1]->setVisibility(false);
    Engine->ZONES[2]->setVisibility(false);
    Engine->ZONES[3]->setVisibility(false);
    Engine->ZONES[4]->setVisibility(false);
    Engine->ZONES[5]->setVisibility(false);
    Engine->ZONES[6]->setVisibility(false);

    //BinaryParser::LoadBVHLevelData("assets/BinaryFiles/INICIO_CIUDAD_MODELS.data", 4);

    cont->musicaJuegoPlay();
    cont->musicaJuegoPause(false);
    cont->musicaMenuStop();

    Engine->crearCamara(90,0.15f,100.f, glm::vec3(2,2,10),glm::vec3(),16.f/9.f);
    //luz = Engine->crearLuz(col,glm::vec3(5, 6, 0),glm::vec3(), Singleton<AssetManager>::Instance()->getShader("Default"));


    // glm::vec3 tmp(40,-21,17);
    // sF->createCollectableWeapon(tmp,3);

    //Engine->setPosition(luz, glm::vec3(125.964005, 10, -46.611977));

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
    // world->setDebug(true);

    //sky.init();


    ParticleSystem_Data PS_D;
    PS_D.Texture = Singleton<AssetManager>::Instance()->getTexture("assets/Textures/Particles/Smoke.png");
    PS_D.SpawnTime = 0.5;
    PS_D.ParticleLifeTime = 4;
    PS_D.MaxParticles = 1/PS_D.SpawnTime * PS_D.ParticleLifeTime;


    BinaryParser::LoadParticleSystem(PS_D, "assets/BinaryFiles/ParticleTest.ps");
    PS = Engine->CreateParticleSystem(Singleton<Omicron>::Instance()->FORWARD_LAYER, PS_D);

    // BillboardBueno* B = new BillboardBueno(-26.074661, -21.048573, 30.194473,"assets/Textures/prueba1.png");
    // Leaf* ParticleNode = new Leaf(Singleton<Omicron>::Instance()->FORWARD_LAYER, B);
    //
    // SkyBox* S = new SkyBox();
    // S->init();
    // Leaf* SkyboxNode = new Leaf(Singleton<Omicron>::Instance()->FORWARD_LAYER, S);

    TData mes;
    mes.add(kDat_total_img,1);
    mes.add(kDat_img1,0);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(129.712,-20.6495,59.8293), 5, 0, false, mes);
    TData mes1;
    mes1.add(kDat_total_img,1);
    mes1.add(kDat_img1,1);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(221.164,-23.4092,35.5667), 5, 0, false, mes1);
    TData mes2;
    mes2.add(kDat_total_img,3);
    mes2.add(kDat_img1,2);
    mes2.add(kDat_img2,3);
    mes2.add(kDat_img3,4);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(330.681,-42.8137,79.0592 ), 5, 0, false, mes2);
    TData mes3;
    mes3.add(kDat_soundRoute,1);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(332.327,-42.8137,60.2511), 10, 0, false, mes3);
    TData mes4;
    mes4.add(kDat_soundRoute,2);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(330.681,-42.8137,87.0592 ), 10, 0, false, mes4);
    TData mes5;
    mes5.add(kDat_soundRoute,3);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(113.177,-21.2692,36.0758), 15, 0, false, mes5);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(355,-28,45), 7, 0, false, mes5);
    TData mes6;
    mes6.add(kDat_soundRoute,4);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(129,-20,70), 6, 0, false, mes6);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(149,-20,62), 6, 0, false, mes6);
    TData mes7;
    mes7.add(kDat_soundRoute,5);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(80,-21,34), 6, 0, false, mes7);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(201,-23,31), 6, 0, false, mes7);

    TData mes8;
    mes8.add(kDat_soundRoute,6);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(255,-43,233), 30, 0, false, mes8);

    TData mes9;
    mes9.add(kDat_total_img,1);
    mes9.add(kDat_img1,5);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(89,-21,33), 5, 0, false, mes9);

    TData mes10;
    mes10.add(kDat_soundRoute,0);
    Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_SoundJumpCliff,1,0,glm::vec3(91,-21,35), 3, 0, false, mes10);

    //TData mes1;
    //mes1.add(kDat_total_img,1);
    //mes1.add(kDat_img1,3);
    //Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(81.9019,2.11054,41.7012), 5, 0, false, mes1);

    Director->init();

    dialogoInicial = new SonidoNormal();
    soundSys->createSound("event:/Voces/Dialogos/DialogoIntro", dialogoInicial);
    // world->setDebug(true);

    UPD = &Game::FirstUpdate;
    MasterClock.Restart();
}

void Game::Update(){
    (this->*UPD)();
}

void Game::FirstUpdate(){

    Engine->BeginDraw();
    Manager->UpdateAll();
    MainCamera->CameraUpdate();
    Engine->draw();
    Engine->drawHUD();

    PopState* estado = new PopState();
    estado->setFadeIn();
    AssetManager* Manager = Singleton<AssetManager>::Instance();
    estado->Addim(Manager->getTextureWithoutSavingToMap("assets/HUD/asdw_esp.png"));
    estado->Addim(Manager->getTextureWithoutSavingToMap("assets/HUD/camara_esp.png"));
    Singleton<StateMachine>::Instance()->AddState(estado);
    UPD = &Game::SecondUpdate;
}

void Game::SecondUpdate(){
    dialogoInicial->play();
    UPD = &Game::NormalUpdate;
    MasterClock.Restart();
    NormalUpdate();
}

void Game::NormalUpdate(){
    // CTransform* cTransform2 = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM,Manager->getHeroID()));
    // std::cout << "POS BUENA:" << glm::to_string(cTransform2->getPosition()) << '\n';

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
    Director->update(DeltaTime);

    //Director->update(DeltaTime);


    soundSys->update();
    //Director->update(DeltaTime);
    //Director->clipingEnemigos();

    //  Interpolation tick!
    Tick = std::min(1.f, static_cast<float>( Accumulator/(1/UPDATE_STEP) ));
    Manager->sendMessageToAllEntities(Message(gg::M_INTERPOLATE, &Tick));

    glm::vec3 pos = playerpos->getPosition();
    pos.y += 3;
    PS->setPosition(pos);

    Engine->BeginDraw();
    Manager->UpdateAll();


    MainCamera->CameraUpdate();

    soundSys->setListenerPosition(MainCamera->getCameraPosition(), MainCamera->getTargetPosition());

    Engine->draw();
    Engine->drawHUD();
    //sky.Draw();

    // DEBUG PATHFINDING
    //glClear(GL_DEPTH_BUFFER_BIT);
    //Singleton<Pathfinding>::Instance()->DroNodes();

    Engine->DisplayFPS();

    // ======================= Debug =======================
    // glClear(GL_DEPTH_BUFFER_BIT);
    // world->debugDrawWorld();
    // Engine->DrawZero();
    // Manager->DibLineas();
    // Director->DrawZones();
    // =====================================================
    Engine->EndDraw();
}

void Game::Resume(){
    Engine->HideCursor(true);
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
    delete dialogoInicial;
}
void Game::Pause(){
    cont->musicaJuegoPause(true);
}
