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
    // Director = Singleton<AIDirector>::Instance();
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
    ZMaterial* MUSHROOM = Singleton<AssetManager>::Instance()->getMaterial("Mushroom");

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


    auto sF = Singleton<Factory>::Instance();
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

    //TData mes1;
    //mes1.add(kDat_total_img,1);
    //mes1.add(kDat_img1,3);
    //Singleton<CTriggerSystem>::Instance()->RegisterTriger(kTrig_InteractMess,1,0,glm::vec3(81.9019,2.11054,41.7012), 5, 0, false, mes1);

    // Director->init();

    dialogoInicial = new SonidoNormal();
    soundSys->createSound("event:/Voces/Dialogos/DialogoIntro", dialogoInicial);
    // world->setDebug(true);

    UPD = &Game::NormalUpdate;
    MasterClock.Restart();

    {
        std::string TEXTO = "GENERATION TIME ";
        TEXTO += std::to_string((uint16_t)(PS->DELAY*1000));
        TEXTO += " miliseconds";
        Engine->hud->GENERATIONTIME.setText(TEXTO);
    }

    {
        std::string TEXTO = "PARTICLE LIFE ";
        TEXTO += std::to_string((uint16_t)(PS->ParticleLifeTime*1000));
        TEXTO += " miliseconds";
        Engine->hud->LIFE.setText(TEXTO);
    }

    {
        std::string TEXTO = "MAX ALPHA ";
        TEXTO += std::to_string((uint16_t)50);
        TEXTO += " percent";

        Engine->hud->MAX_ALPHA.setText(TEXTO);
    }
}

void Game::Update(){
    (this->*UPD)();
}

void Game::FirstUpdate(){

    NormalUpdate();

    PopState* estado = new PopState();
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
    // Director->update(DeltaTime);

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
    entregableParticleSystem();
}

void Game::entregableParticleSystem(){
    if(Engine->key(gg::U, true)){
        if(PS->DELAY < 5){
            PS->DELAY += 0.1f;
            std::string TEXTO = "GENERATION TIME ";
            TEXTO += std::to_string((uint16_t)(PS->DELAY*1000));
            TEXTO += " miliseconds";
            Engine->hud->GENERATIONTIME.setText(TEXTO);
        }
    }
    else if(Engine->key(gg::J, true)){
        if(PS->DELAY > 0.2){
            PS->DELAY -= 0.1f;
            std::string TEXTO = "GENERATION TIME ";
            TEXTO += std::to_string((uint16_t)(PS->DELAY*1000));
            TEXTO += " miliseconds";
            Engine->hud->GENERATIONTIME.setText(TEXTO);
        }
    }

    if(Engine->key(gg::I, true)){
        if(PS->ParticleLifeTime < 10){
            PS->ParticleLifeTime += 0.1f;
            std::string TEXTO = "PARTICLE LIFE ";
            TEXTO += std::to_string((uint16_t)(PS->ParticleLifeTime*1000));
            TEXTO += " miliseconds";
            Engine->hud->LIFE.setText(TEXTO);
        }
    }
    else if(Engine->key(gg::K, true)){
        if(PS->ParticleLifeTime > 0.2){
            PS->ParticleLifeTime -= 0.1f;
            std::string TEXTO = "PARTICLE LIFE ";
            TEXTO += std::to_string((uint16_t)(PS->ParticleLifeTime*1000));
            TEXTO += " miliseconds";
            Engine->hud->LIFE.setText(TEXTO);
        }
    }

    if(Engine->key(gg::O, true)){
        if(PS->MAXALPHA < 255){
            PS->MAXALPHA += 5;
            std::string TEXTO = "MAX ALPHA ";
            uint16_t A =  (uint16_t)((PS->MAXALPHA/255.f)*100);
            TEXTO += std::to_string(A);
            TEXTO += " percent";
            Engine->hud->MAX_ALPHA.setText(TEXTO);
        }
    }
    else if(Engine->key(gg::L, true)){
        if(PS->MAXALPHA > 0) {
            PS->MAXALPHA += 5;
            std::string TEXTO = "MAX ALPHA ";
            uint16_t A =  (uint16_t)((PS->MAXALPHA/255.f)*100);
            TEXTO += std::to_string(A);
            TEXTO += " percent";

            Engine->hud->MAX_ALPHA.setText(TEXTO);
        }
    }
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
