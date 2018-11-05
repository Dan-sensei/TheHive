#include <iostream>
#include <cstdint>
#include <iomanip>
#include <map>
#include <string>

#include "Arena.hpp"
#include "ObjectManager.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Util.hpp"
#include "Singleton.hpp"
#include "InitStructs.hpp"

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
    engine = Singleton<GameEngine>::Instance();
    engine->Starto();
    engine->HideCursor(true);
}

Game::~Game(){

}

void Game::RUN(){

    //uint8_t* p;

    ObjectManager* Manager = Singleton<ObjectManager>::Instance();
    Manager->initObjectManager();

    uint16_t hero = Manager->createEntity();
    std::cout << "Hero " << hero << std::endl;

    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    ICTransform CTransformInitData(0, 0, 0, 0, 0, 0, 0, 0, 0);
    ICRenderable_3D CRenderable_3DInitData("assets/Models/obradearte/algo.obj", moradoDeLos80);

    Manager->addComponentToEntity(gg::TRANSFORM, hero, &CTransformInitData);
    Manager->addComponentToEntity(gg::KEYBOARD, hero);
    Manager->addComponentToEntity(gg::RENDERABLE_3D, hero, &CRenderable_3DInitData);

    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");

    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    Camera camera = engine->createCamera(gg::Vector3f(50, 0, -100), gg::Vector3f(0, 0, 50));
    ////camera.setPosition(gg::Vector3f(-50, 0, 100));
    ////camera.setTarget(gg::Vector3f(0, 0, 50));

    while(engine->isWindowOpen()) {
        Manager->sendMessageToAllEntities(gg::M_UPDATE);
        engine->Dro();
        engine->DisplayFPS();
    }
}

void Game::CLIN(){
    engine->clean();
}
