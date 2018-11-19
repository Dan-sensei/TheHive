#include <iostream>
#include <cstdint>
#include <iomanip>
#include <map>
#include <string>

#include "Arena.hpp"
#include "ComponentArch/ObjectManager.hpp"
#include "ComponentArch/InitStructs.hpp"
#include "GameEngine/Camera.hpp"
#include "Game.hpp"
#include "Util.hpp"
#include "Singleton.hpp"

#include "EventSystem/Agent.hpp"
#include "EventSystem/GameState.hpp"
#include "GameAI/Pathfinding.hpp"



#define MOVEMENT_SPEED 1.f


//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
void printHexVal(uint16_t val) {
   std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         std::cout << " ";
      }
      std::cout << "\n";
   }
}
//============================================================================================

Game::Game(){
    Engine = Singleton<GameEngine>::Instance();
    Engine->Starto();
    Engine->HideCursor(true);

    Manager = Singleton<ObjectManager>::Instance();
    Manager->initObjectManager();
}

Game::~Game(){

}

void Game::RUN(){

    Engine->createCamera(gg::Vector3f(0, 0, 0), gg::Vector3f(0, 0, 50));
    {
        Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
        uint16_t hero = Manager->createEntity();
        InitCTransform CTransformInitData(0, 0, 10, 0, 0, 0);
        InitCRenderable_3D CRenderable_3DInitData("assets/Models/obradearte/algo.obj", moradoDeLos80);
        Manager->addComponentToEntity(gg::TRANSFORM, hero, &CTransformInitData);
        Manager->addComponentToEntity(gg::CAMERA, hero);
        Manager->addComponentToEntity(gg::KEYBOARD, hero);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, hero, &CRenderable_3DInitData);
        //Manager->removeComponentFromEntity(gg::RENDERABLE_3D, hero);

        uint16_t cube1 = Manager->createEntity();
        InitCTransform CTransformCube1(50,0,0,0,0,0);
        InitCRenderable_3D CRenderableCube1("assets/Models/Cube.obj", moradoDeLos80);
        Manager->addComponentToEntity(gg::TRANSFORM, cube1, &CTransformCube1);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, cube1, &CRenderableCube1);
        //Manager->removeEntity(cube1);
    }

    //{
    //    Material AgujeroNegro("assets/Textures/ice.bmp");
    //    InitCRenderable_3D InitTrainingArea("assets/Models/TrainingArea.obj", AgujeroNegro);
    //    uint16_t TrainingArea = Manager->createEntity();
    //    Manager->addComponentToEntity(gg::RENDERABLE_3D, TrainingArea, &InitTrainingArea);
    //}
    {
        uint16_t Actor1 = Manager->createEntity();
        Material Blue("assets/Textures/Blue.png");
        InitCTransform Actor1Transform(0,0,0,0,0,0);
        InitCRenderable_3D CRenderableCube1("assets/Models/Actor.obj", Blue);
        Manager->addComponentToEntity(gg::TRANSFORM, Actor1, &Actor1Transform);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, Actor1, &CRenderableCube1);
        Manager->addComponentToEntity(gg::PATHFINDING, Actor1);
    }

    {
        Material Wireframe("assets/NavMeshes/Navmesh.png");
        uint16_t Navmesh = Manager->createEntity();
        InitCTransform init(0,0,0,0,0,0);
        InitCRenderable_3D InitTrainingArea("assets/NavMeshes/Test.obj", Wireframe);
        Manager->addComponentToEntity(gg::TRANSFORM, Navmesh, &init);
        Manager->addComponentToEntity(gg::RENDERABLE_3D, Navmesh, &InitTrainingArea);
    }

    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");

    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    std::cout << "BEGIN GAME LOOP" << '\n';
    while(Engine->isWindowOpen()) {
        Engine->BeginDro();

        Manager->sendMessageToAllEntities(gg::M_UPDATE);
        Engine->Dro();
        Engine->DisplayFPS();

        Singleton<Pathfinding>::Instance()->DroNodes();

        Engine->EndDro();
    }
}

void Game::CLIN(){
    Manager->clin();
    Engine->clean();
}
