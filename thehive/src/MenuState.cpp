#include "MenuState.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include "GameEngine/ScreenConsole.hpp"

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

MenuState::MenuState():cont(){
    Engine = Singleton<TMotorTAG>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();

    //Engine->Starto();
    //Engine->HideCursor(true);
    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();
    //Engine->HideCursor(false);
}

MenuState::~MenuState(){

}

void MenuState::Init(){

    cont.setposmax(Singleton<ScreenConsole>::Instance()->InitMenu());
    //Engine->createCamera(glm::vec3(0, 30, 30), glm::vec3(0, 0, 0));
}
void MenuState::Resume() {
    cont.setposmax(Singleton<ScreenConsole>::Instance()->InitMenu());
    //Engine->HideCursor(false);

}
//void MenuState::submenu(){
//    CLIN();

//}
void MenuState::Update(){
    Engine->BeginDraw();
    Engine->draw();
    cont.update();
    Singleton<ScreenConsole>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    Engine->EndDraw();
}

void MenuState::CLIN(){
    Singleton<ScreenConsole>::Instance()->CLINMenu();

    Blackboard::ClearGlobalBlackboard();
    Manager->clin();
    world->clean();
    EventSystem->clin();
}
