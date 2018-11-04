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
    engine.Starto();
    engine.HideCursor(true);
}

Game::~Game(){

}

void Game::RUN(){

    uint8_t* p;

    ObjectManager* Manager = Singleton<ObjectManager>::Instance();
    Manager->initObjectManager();

    Camera* camera = Singleton<Camera>::Instance();

    uint16_t hero = Manager->createEntity();
    std::cout << "Hero " << hero << std::endl;

    Manager->addComponentToEntity(gg::TRANSFORM, hero);

    Manager->sendMessageToAllEntities(gg::M_UPDATE);
    Manager->sendMessageToAllEntities(gg::M_UPDATE);
    Manager->sendMessageToAllEntities(gg::M_UPDATE);

    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");

    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    //Camera camera = engine.createCamera(gg::Vector3f(50, 0, -100), gg::Vector3f(0, 0, 50));
    ////camera.setPosition(gg::Vector3f(-50, 0, 100));
    ////camera.setTarget(gg::Vector3f(0, 0, 50));

    //while(engine.isWindowOpen()) {

    //    gg::Vector3f nextPosition = tioPablomanesQueNoEstaTanMal.getPosition();

    //    if(engine.key(gg::GG_W))
    //        nextPosition.Z += MOVEMENT_SPEED;
    //    else if(engine.key(gg::GG_S))
    //        nextPosition.Z -= MOVEMENT_SPEED;

    //    if(engine.key(gg::GG_A))
    //        nextPosition.X -= MOVEMENT_SPEED;
    //    else if(engine.key(gg::GG_D))
    //        nextPosition.X += MOVEMENT_SPEED;

    //    tioPablomanesQueNoEstaTanMal.setPosition(nextPosition);

    //    engine.Dro();
    //    engine.DisplayFPS();
    //}
}

void Game::CLIN(){
    engine.clean();
}
