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

#include "GameEngine/Billboard.hpp"

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
    auto sF = Singleton<Factory>::Instance();

    Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));

    // sF->createHero(gg::Vector3f(700, 100, 0),false);
    sF->createHero(gg::Vector3f(1061, 105, 344),false);
    sF->createEnemy(gg::Vector3f(740, 100, 20));
    sF->createEnemy(gg::Vector3f(740, 100, 30));
    sF->createEnemy(gg::Vector3f(740, 100, 40));

    gg::Vector3f mapPos(700,120,0);
    sF->createCollisionableStaticModel(
        "assets/Models/CIUDAD/PROTOTIPO5/PROTOTIPO_CIUDAD.obj",
        "assets/Models/CIUDAD/PROTOTIPO5/PROTOTIPO_CIUDAD.bullet",
        "assets/Models/CIUDAD/PROTOTIPO5/PROTOTIPO_CIUDAD.png",
        mapPos
    );

    // Armas
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 20),0);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 40),1);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 60),2);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 80),3);
    sF->createCollectableWeapon(gg::Vector3f(700, 100, 100),4);

    // Eventos?
    uint16_t idEx = sF->createCollisionableDynamicModel(
        "assets/Models/ModelsForEvents/door1.obj",
        "assets/Models/ModelsForEvents/door1.bullet",
        "assets/Textures/Domino.jpg",
        gg::Vector3f(mapPos.X+412, mapPos.Y-13, mapPos.Z+122));
    sF->createTouchableObject(gg::Vector3f(mapPos.X+425, mapPos.Y-23, mapPos.Z+134),idEx,gg::Vector3f(0,0.1,0),3200);

    idEx = sF->createCollisionableDynamicModel(
        "assets/Models/ModelsForEvents/door2.obj",
        "assets/Models/ModelsForEvents/door2.bullet",
        "assets/Textures/Domino.jpg",
        gg::Vector3f(mapPos.X+331.65, mapPos.Y-18, mapPos.Z+45.78));
    sF->createTouchableObject(gg::Vector3f(mapPos.X+354, mapPos.Y-23, mapPos.Z+38),idEx,gg::Vector3f(0,-0.035,0),8000);

    ////////////////////////////////////////////////////////////////
    // TABLA MOLONA DE CONVERSION DE LA POSICION EN EL ESPACIO 3D //
    ////////////////////////////////////////////////////////////////
    //              X        Y       Z                            //
    // ---------------------------------------------------------- //
    // BELNDER  -> bX,      bY,     bZ                            //
    // JEUGO    -> jX-bX,   jY+bZ,  jZ-bY                         //
    ////////////////////////////////////////////////////////////////

    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //// std::cout << "--------------\n";

    //Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    //Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");
    //tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

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
    Manager->clin();
    Engine->clean();
    world->clean();
    EventSystem->clin();
}
