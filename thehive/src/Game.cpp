#include "Game.hpp"

//#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "GameEngine/Camera.hpp"
#include "Singleton.hpp"
#include "GameAI/Pathfinding.hpp"
#include "GameAI/AIDirector.hpp"
#include "GameAI/NavmeshStructs.hpp"

#include "GameEngine/Motor2D.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>
#include "BinaryParser.hpp"
#include <SurrealEngine/SurrealEngine.hpp>

#include <GameEngine/Motor2D.hpp>

#include <SurrealEngine/BillboardBueno.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager



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
    Engine = Singleton<SurrealEngine>::Instance();
    Engine2D = Singleton<Motor2D>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    Director = Singleton<AIDirector>::Instance();

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

    BinaryParser::ReadNatureData("assets/BinaryFiles/NATURE.data");

    BinaryParser::ReadLoadZonesData("assets/BinaryFiles/LOADZONES.data");
    BinaryParser::ReadUnLoadZonesData("assets/BinaryFiles/UNLOADZONES.data");
    BinaryParser::ReadEventsData("assets/BinaryFiles/EVENTOS.data");
    BinaryParser::LoadLevelData("assets/BinaryFiles/INICIO.data", 1);
    // BinaryParser::LoadLevelData("assets/BinaryFiles/ESTACION.data");
    // BinaryParser::LoadLevelData("assets/BinaryFiles/POST_ESTACION.data");
    // BinaryParser::LoadLevelData("assets/BinaryFiles/CALLE_PRINCIPAL.data");
    // BinaryParser::LoadLevelData("assets/BinaryFiles/PASEO.data");
    // BinaryParser::LoadLevelData("assets/BinaryFiles/PARQUE.data");
    // BinaryParser::LoadLevelData("assets/BinaryFiles/TAMESIS.data");
    // BinaryParser::LoadLevelData("assets/BinaryFiles/END.data");

    auto sF = Singleton<Factory>::Instance();
    Engine->crearCamara(90,0.15f,300.f, glm::vec3(2,2,10),glm::vec3(),16.f/9.f);
    luz = Engine->crearLuz(col,glm::vec3(5, 6, 0),glm::vec3(), Singleton<AssetManager>::Instance()->getShader("Default"));
    // Pos init del heroe normal
    // 360, 0, 350
    Engine->HideCursor(true);

    float fuerzaalign=0.1;//no se usa
    float mindist,fuerzasep,fuerzacoh,numsawrm;//15
    //uint16_t h = BinaryParser::ReadRespawnNodesData("assets/BinaryFiles/RESPAWN.data");
    uint16_t h = sF->createHero(glm::vec3(107.694,3.885,-40.4267),-1);
    //mindist=5;//minima distancia para aplica separacion 0.8 buena
    //fuerzasep=20;//10
    //fuerzacoh=10;//10
    //numsawrm=15;//15
    sF->createSwarm(glm::vec3(108.141,3.885,-62.4015),100,mindist, fuerzasep, fuerzacoh, fuerzaalign,numsawrm);
    sF->createSoldier(glm::vec3(108.141,3.885,-62.4015),100);
    //CFlock* cFlock = new CFlock(false,mindist, fuerzasep, fuerzacoh, fuerzaalign);
    //Manager->addComponentToEntity(cFlock, gg::FLOCK, me);


    //mindist=20;//minima distancia para aplica separacion 0.8 buena
    //fuerzasep=20;//10
    //fuerzacoh=10;//10
    //sF->createSwarm(glm::vec3(106.698,3.885,-30.4306),100,mindist, fuerzasep, fuerzacoh, fuerzaalign,numsawrm);
    //mindist=20;//minima distancia para aplica separacion 0.8 buena
    //fuerzasep=10;//10
    //fuerzacoh=20;//10
    //sF->createSwarm(glm::vec3(116.484,3.885,-24.2306),100,mindist, fuerzasep, fuerzacoh, fuerzaalign,numsawrm);
    //mindist=5;//minima distancia para aplica separacion 0.8 buena
    //fuerzasep=20;//10
    //fuerzacoh=10;//10
    //numsawrm=5;//15
    //sF->createSwarm(glm::vec3(120.253,3.885,-49.034),100,mindist, fuerzasep, fuerzacoh, fuerzaalign,numsawrm);
    //mindist=20;//minima distancia para aplica separacion 0.8 buena
    //fuerzasep=20;//10
    //fuerzacoh=10;//10
    //sF->createSwarm(glm::vec3(120.499,3.885,-39.8585),100,mindist, fuerzasep, fuerzacoh, fuerzaalign,numsawrm);
    //mindist=20;//minima distancia para aplica separacion 0.8 buena
    //fuerzasep=10;//10
    //fuerzacoh=20;//10
    //sF->createSwarm(glm::vec3(124.812,3.885,-56.4019),100,mindist, fuerzasep, fuerzacoh, fuerzaalign,numsawrm);

//1--(108.141,3.885,-62.4015)
//2--(106.698,3.885,-30.4306)
//3--(116.484,3.885,-24.2306)
//4--(127.983,3.885,-37.4344)
//5-- (120.499,3.885,-39.8585)
//6--(124.812,3.885,-56.4019)


    //(108.041,3.885,-54.3579)
    //uint16_t Factory::createSwarm( const glm::vec3 &Position,const float &health) {


    // uint16_t h = sF->createHero(glm::vec3(451,17,54),-1);

    //for (size_t i = 0; i < 50; i++) {
    //}
    //sF->createRusher(glm::vec3(0, 6, 0), 10);
    //sF->createRusher(glm::vec3(5,3,65),200);


    // Director->init();   // IADIRECTOR

    MainCamera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, h));
    playerpos = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, h));

    //sF->createSoldier(playerpos->getPosition(), 10);

    // uint16_t n = Manager->createEntity();
    // CStaticModel* m = new CStaticModel("assets/BinaryFiles/BinaryModels/NavmeshCITY.modelgg", AssetManager::getMaterial("Nav"), glm::vec3(0,3,0), glm::vec3());
    // Manager->addComponentToEntity(m,gg::STATICMODEL,n);


    Accumulator = 0;

    //Singleton<Pathfinding>::Instance()->SetDebug(true);
    world->setDebug(true);
    MasterClock.Restart();
    Engine2D->InitHUD();

    sky.init();
    //Engine2D->prueba();
    // //std::cout << "\n -- INIT -- " << '\n';
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
    pos.y += 7;
    Engine->setPosition(luz, pos);
    // //std::cout << " - BEGIN DRAW" << '\n';
    Engine->BeginDraw();

    // //std::cout << "  - UPDATE ALL" << '\n';
    Manager->UpdateAll();

    ////std::cout << "Update" << '\n';
    MainCamera->CameraUpdate();
    //Engine->print();

    // //std::cout << "  - DRAW" << '\n';
    Engine->draw();

    Engine->DisplayFPS();
    BillboardBueno bill(107.694,3.885,-40.4267,"assets/HUD/ojetecalor.png");
    bill.Draw();
    sky.Draw();
    Engine2D->DisplayHUD();

    //Engine2D->draw();
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

    //Engine->HideCursor(true);
}

void Game::CLIN(){
    //Blackboard::ClearGlobalBlackboard();
    Manager->clin();
    world->clear();

    //Engine2D->CLINNormal();
    //EventSystem->clin();

    // //std::cout << "1/60 = " << 1/60.F << '\n';
    // //std::cout << "UPDTES " << UPDATE  << '\n';
    // //std::cout << "DRO " << DRO  << '\n';

}
