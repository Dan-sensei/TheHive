#include "PauseState.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include "GameEngine/ScreenConsole.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>
#include <States/StateMachine.hpp>


#define MOVEMENT_SPEED 1.f



PauseState::PauseState():cont(){
    Engine = Singleton<TMotorTAG>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();

    //Engine->Starto();
    //Engine->HideCursor(true);
    Manager = Singleton<ObjectManager>::Instance();

    world = Singleton<ggDynWorld>::Instance();
    //world->inito();
    //Engine->HideCursor(false);
}

PauseState::~PauseState(){

}

void PauseState::Init(){

    Singleton<ScreenConsole>::Instance()->InitPause();
    //Engine->createCamera(gg::Vector3f(0, 30, 30), gg::Vector3f(0, 0, 0));
}
 void PauseState::Resume(){
    Init();
}
//void PauseState::submenu(){
//    CLIN();

//}
void PauseState::Update(){

    Engine->BeginDraw();
    Engine->draw();
    cont.update();
    Singleton<ScreenConsole>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    Engine->EndDraw();
}

void PauseState::CLIN(){
    Singleton<ScreenConsole>::Instance()->CLINMenu();

    //Blackboard::ClearGlobalBlackboard();
    //Manager->clin();
    //world->clear();
    //EventSystem->clin();
}
