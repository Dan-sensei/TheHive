#include "IAState.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "Singleton.hpp"

#include <EventSystem/CTriggerSystem.hpp>
#include <Bullet/ggDynWorld.hpp>
#include "GameEngine/ScreenConsole.hpp"

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

IAState::IAState(int _id):cont(),id(_id){
    Engine = Singleton<TMotorTAG>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    //Engine->Starto();
    //Engine->HideCursor(true);

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();
    //Engine->HideCursor(false);
}

IAState::~IAState(){

}

void IAState::Init(){

    cont.setposmax(Singleton<ScreenConsole>::Instance()->InitAIDebug(id));
    //Engine->createCamera(glm::vec3(0, 30, 30), glm::vec3(0, 0, 0));
}
void IAState::Resume() {
    cont.setposmax(Singleton<ScreenConsole>::Instance()->InitAIDebug(id));

}
//void IAState::submenu(){
//    CLIN();

//}
void IAState::Update(){
    Engine->BeginDraw();
    Engine->draw();
    cont.update();
    Singleton<ScreenConsole>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    Engine->EndDraw();
}

void IAState::CLIN(){
    Singleton<ScreenConsole>::Instance()->CLINMenu();
}
