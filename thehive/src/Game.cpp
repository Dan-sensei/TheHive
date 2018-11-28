#include "Game.hpp"

#include <iostream>
#include <cstdint>
#include <string>

#include "ComponentArch/ObjectManager.hpp"
#include "GameEngine/Camera.hpp"
#include "Singleton.hpp"

#include "GameAI/Pathfinding.hpp"

#include "GameEngine/ScreenConsole.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>

#define MOVEMENT_SPEED 1.f


//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
void printHexVal(uint16_t val) {
   // std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      // std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         // std::cout << " ";
      }
      // std::cout << "\n";
   }
}
//============================================================================================

Game::Game(){
    Engine = Singleton<GameEngine>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();

    Engine->Starto();
    Engine->HideCursor(true);

    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
    world->inito();
}

Game::~Game(){

}

void Game::RUN(){

    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));

    Factory* factory = Singleton<Factory>::Instance();
    factory->createHero(gg::Vector3f(600, 180, 0));
    factory->createEnemy(gg::Vector3f(570, 190, 0));
    //factory->createCollisionableStaticModel("assets/Models/CIUDAD/PROTOTIPO_CIUDAD.obj", "assets/Models/CIUDAD/PROTOTIPO_CIUDAD.bullet", "assets/Models/CIUDAD/PROTOTIPO_CIUDAD.png", gg::Vector3f(700, 175, 0));
    uint16_t Dummy = factory->createPathFindingActor(gg::Vector3f(150, 83, 450));
    //factory->createStaticModel("assets/NavMeshes/L4D2Nav.obj", "assets/NavMeshes/L4D2Nav.png", gg::Vector3f(0, 0, 0));

    uint16_t Navmesh = Manager->createEntity();
    Material yelo("assets/NavMeshes/L4D2Nav.png");

    CTransform* Transform = new CTransform(gg::Vector3f(0,0,0), gg::Vector3f(0,0,0));
    Manager->addComponentToEntity(Transform, gg::TRANSFORM, Navmesh);

    CRenderable_3D* Renderable_3D = new CRenderable_3D("assets/NavMeshes/L4D2Nav.obj", yelo);
    Manager->addComponentToEntity(Renderable_3D, gg::RENDERABLE_3D, Navmesh);

    uint16_t NavmeshGround = Manager->createEntity();
    CRigidBody* RigidBody = new CRigidBody(false,"", 0, -10, 0, 680,10,800, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody, gg::RIGID_BODY, NavmeshGround);




    uint16_t Wall_1 = Manager->createEntity();
    CRigidBody* RigidBody_1 = new CRigidBody(false,"", -280, 0, -100, 160, 100,265, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody_1, gg::RIGID_BODY, Wall_1);

    uint16_t Wall_2 = Manager->createEntity();
    CRigidBody* RigidBody_2 = new CRigidBody(false,"", -80, 0, 410, 215, 100,320, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody_2, gg::RIGID_BODY, Wall_2);

    uint16_t Wall_3 = Manager->createEntity();
    CRigidBody* RigidBody_3 = new CRigidBody(false,"", 110, 0, 70, 80, 100, 32, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody_3, gg::RIGID_BODY, Wall_3);

    uint16_t Wall_4 = Manager->createEntity();
    CRigidBody* RigidBody_4 = new CRigidBody(false,"", -25, 0, 17, 100, 125, 28, 0, 0,0,0, 0.2);
    Manager->addComponentToEntity(RigidBody_4, gg::RIGID_BODY, Wall_4);

    //60 -450
    //132 - 550
    CNavmeshAgent* Agent = static_cast<CNavmeshAgent*>(Manager->getComponent(gg::NAVMESHAGENT, Dummy));
    Agent->SetDestination(gg::Vector3f(373, 0, -430));

    // std::cout << "BEGIN GAME LOOP" << '\n';
    gg::cout("Testing", gg::Color(255, 0, 0, 1));

    world->setDebug(true);
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
    }
}

void Game::CLIN(){
    Manager->clin();
    Engine->clean();
    world->clean();
    EventSystem->clin();
}
