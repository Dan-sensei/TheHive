#include "IAState.hpp"

//#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "Singleton.hpp"

#include <EventSystem/CTriggerSystem.hpp>
#include <Bullet/ggDynWorld.hpp>
#include "GameEngine/Motor2D.hpp"

#include <States/StateMachine.hpp>


#define MOVEMENT_SPEED 1.f


//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
/*
void printHexVal(uint16_t val) {
   // //std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      // //std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         // //std::cout << " ";
      }
      // //std::cout << "\n";
   }
}
*/
//============================================================================================

IAState::IAState(int _id):cont(_id),id(_id){
    Engine = Singleton<SurrealEngine>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    //Engine->Starto();
    //Engine->HideCursor(true);

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();
    //Engine->HideCursor(false);
    Engine->HideCursor(false);
    
}

IAState::~IAState(){

}

void IAState::Init(){

    Singleton<Motor2D>::Instance()->InitAIDebug(id);
    //Engine->createCamera(glm::vec3(0, 30, 30), glm::vec3(0, 0, 0));
}
void IAState::Resume() {
    Singleton<Motor2D>::Instance()->InitAIDebug(id);

}
//void IAState::submenu(){
//    CLIN();

//}
void IAState::Update(){
    Engine->PollEvents();

    Engine->BeginDraw();
    Engine->draw();
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

void IAState::CLIN(){
    Singleton<Motor2D>::Instance()->CLINMenu();
}
