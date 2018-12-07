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
    auto sF = Singleton<Factory>::Instance();
    uint16_t key;

    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));


    // sF->createHero(gg::Vector3f(700, 100, 0),false);
    sF->createHero(gg::Vector3f(1760, 110, 350),false);     //600
    sF->createEnemy(gg::Vector3f(740, 100, 20));
    sF->createEnemy(gg::Vector3f(740, 100, 30));
    sF->createEnemy(gg::Vector3f(740, 100, 40));
    sF->createEnemy(gg::Vector3f(1760, 110, 390));
    sF->createHero(gg::Vector3f(1797, 120, 300),false);
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
    }
}

void Game::CLIN(){
    Blackboard::ClearGlobalBlackboard();
    Manager->clin();
    Engine->clean();
    world->clean();
    EventSystem->clin();
}
