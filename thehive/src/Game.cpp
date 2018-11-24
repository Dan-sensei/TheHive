#include <iostream>
#include <cstdint>
#include <iomanip>
#include <map>
#include <string>

#include "Arena.hpp"
#include "ComponentArch/ObjectManager.hpp"
#include "GameEngine/Camera.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "Singleton.hpp"

#include "ComponentArch/Components/CAgent.hpp"
#include <EventSystem/EnumTriggerType.hpp>
#include "GameAI/Pathfinding.hpp"


#include "Bullet/ggDynWorld.hpp"
#include "GameEngine/ScreenConsole.hpp"

#include "BT/BehaviorTree.hpp"
#include "BT/RandomSelector.hpp"
#include "BT/RandomSequence.hpp"
#include "BT/Action.hpp"

#include "EventSystem/Blackboard.hpp"
#include "EventSystem/BData.hpp"
#include "EventSystem/BInt.hpp"
#include "EventSystem/BFloat.hpp"

#include "Factory.hpp"

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

    {

        // ---------------------------------------

        // Cubo pequeño
        // uint16_t cube1 = Manager->createEntity();
        // InitCTransform CTransformCube1(50,0,0,0,0,0);
        // InitCRenderable_3D CRenderableCube1("assets/Models/Cube.obj", moradoDeLos80);
        // InitCRigidBody CRigidBodyCube1(true,"assets/BoundingBoxes/Cube.bullet",  50,20,10, -1,-1,-1, 10, 0,0,0);
        // Manager->addComponentToEntity(gg::TRANSFORM, cube1, &CTransformCube1);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, cube1, &CRenderableCube1);
        // Manager->addComponentToEntity(gg::RIGID_BODY, cube1, &CRigidBodyCube1);
        //
        // InitCAgent objetoExplosion(kTrig_Explosion);
        // Manager->addComponentToEntity(gg::CAGENT, cube1, &objetoExplosion);

        // Cubo grande
        // uint16_t cube2 = Manager->createEntity();
        // InitCTransform CTransformCube2(0,0,0,0,0,0);
        // InitCRenderable_3D CRenderableCube2("assets/Models/cuboGrande.obj", moradoDeLos80);
        // InitCRigidBody CRigidBodyCube2(true,"assets/BoundingBoxes/cuboGrande.bullet", 0,100,50, -1,-1,-1, 50, 0,0,0);
        // // InitCRigidBody CRigidBodyCube2(false,"",  0,100,50, 50,50,50, 50, 0,0,0);
        // Manager->addComponentToEntity(gg::TRANSFORM, cube2, &CTransformCube2);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, cube2, &CRenderableCube2);
        // Manager->addComponentToEntity(gg::RIGID_BODY, cube2, &CRigidBodyCube2);
        //
        // // Se usa para el RAYCASTING para el debug visual
        // // QUE ESTE SIEMPRE EN LA POSICION 4 DE CREACION
        // uint16_t cube3 = Manager->createEntity();
        // InitCTransform CTransformCube3(0,20,0,0,0,0);
        // InitCRenderable_3D CRenderableCube3("assets/Models/Cube.obj", moradoDeLos80);
        // Manager->addComponentToEntity(gg::TRANSFORM, cube3, &CTransformCube3);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, cube3, &CRenderableCube3);
        //

        //    Material pipaDeLos90("assets/Textures/arma.jpeg");


        // // Entidad tipo arma
        // // En cuanto pasa el heroe por encima, se le anyade una componente arma, si no la tiene
        // uint16_t Arma1 = Manager->createEntity();
        // InitCTransform CTransformArma1(100,5,50,0,0,0);
        // InitCRenderable_3D CRenderableArma1("assets/Models/Cube.obj", pipaDeLos90);
        // Manager->addComponentToEntity(gg::TRANSFORM, Arma1, &CTransformArma1);
        // Manager->addComponentToEntity(gg::RENDERABLE_3D, Arma1, &CRenderableArma1);


    }

    Singleton<Factory>::Instance()->createHero(gg::Vector3f(700, 180, 0));
    Singleton<Factory>::Instance()->createEnemy(gg::Vector3f(710, 180, 0));
    Singleton<Factory>::Instance()->createCollisionableStaticModel("assets/Models/prueba.obj", "assets/BoundingBoxes/prueba.bullet", "assets/Textures/ice.bmp", gg::Vector3f(700, 175, 0));
    Singleton<Factory>::Instance()->createPathFindingActor(gg::Vector3f(100, 83, 13));
    Singleton<Factory>::Instance()->createStaticModel("assets/NavMeshes/L4D2Nav.obj", "assets/NavMeshes/L4D2Nav.png", gg::Vector3f(0, 0, 0));


    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //// std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");
    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    // std::cout << "BEGIN GAME LOOP" << '\n';
    gg::cout("Testing", gg::Color(255, 0, 0, 1));

    world->setDebug(false);
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
