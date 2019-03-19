#include "MenuState.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include "GameEngine/Motor2D.hpp"
#include <EventSystem/CTriggerSystem.hpp>
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
    Engine = Singleton<SurrealEngine>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    Engine->HideCursor(false);
}

MenuState::~MenuState(){
    CLIN();

}

void MenuState::Init(){

    Singleton<Motor2D>::Instance()->InitMenu();
    //Singleton<Motor2D>::Instance()->prueba();
    Engine->HideCursor(false);

    //musica_menu->play();

    //Engine->createCamera(glm::vec3(0, 30, 30), glm::vec3(0, 0, 0));
}
void MenuState::Resume() {
    Singleton<Motor2D>::Instance()->InitMenu();
    //Singleton<Motor2D>::Instance()->prueba();
    Engine->HideCursor(false);

}
//void MenuState::submenu(){
//    CLIN();

//}
void MenuState::Update(){
    Engine->PollEvents();

    Engine->BeginDraw();
    //Engine->draw();
    cont.update();
    //Singleton<Motor2D>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    Singleton<Motor2D>::Instance()->draw();
    Singleton<Motor2D>::Instance()->checkbuton();
    Singleton<Motor2D>::Instance()->aplyhover();
    //Engine2D->draw();
    //Engine2D->checkbuton();

    Engine->EndDraw();
    Engine->resetClicked();
}

void MenuState::CLIN(){
    Singleton<Motor2D>::Instance()->CLINMenu();
    EventSystem->clin();
}
