#include "OptionState.hpp"

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
#include <States/StateMachine.hpp>


#define MOVEMENT_SPEED 1.f


//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
/*
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
*/
//============================================================================================

OptionState::OptionState():cont(){
    Engine = Singleton<TMotorTAG>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();

    //Engine->Starto();
    //Engine->HideCursor(true);
    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();
    //Engine->HideCursor(false);
}

OptionState::~OptionState(){

}

void OptionState::Init(){
    cont.setposmax(Singleton<ScreenConsole>::Instance()->InitMenu4());
    //Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));
}
void OptionState::Resume() {
    Init();

}
//void OptionState::submenu(){
//    CLIN();

//}
void OptionState::Update(){
    Engine->BeginDraw();
    Engine->draw();
    cont.update();
    Singleton<ScreenConsole>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    Engine->EndDraw();
}

void OptionState::CLIN(){
    Singleton<ScreenConsole>::Instance()->CLINMenu();

    //Blackboard::ClearGlobalBlackboard();
    //Manager->clin();
    //world->clean();
    //EventSystem->clin();
}
