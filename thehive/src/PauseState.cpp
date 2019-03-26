#include "PauseState.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include "GameEngine/Motor2D.hpp"

#include "Factory.hpp"
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <EventSystem/Blackboard.hpp>
#include <States/StateMachine.hpp>
#include "GameEngine/Motor2D.hpp"



#define MOVEMENT_SPEED 1.f



PauseState::PauseState():cont(){
    Engine = Singleton<SurrealEngine>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    sky.init();
}

PauseState::~PauseState(){
    CLIN();

}

void PauseState::Init(){

    Engine->HideCursor(false);
    Singleton<Motor2D>::Instance()->InitPause();
    //Engine->createCamera(glm::vec3(0, 30, 30), glm::vec3(0, 0, 0));
}
 void PauseState::Resume(){

    Init();
}
//void PauseState::submenu(){
//    CLIN();

//}
void PauseState::Update(){

    Engine->PollEvents();

    Engine->BeginDraw();
    Engine->draw();
    cont.update();
    //Singleton<Motor2D>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    sky.Draw();
    Singleton<Motor2D>::Instance()->draw();
    Singleton<Motor2D>::Instance()->checkbuton();
    Singleton<Motor2D>::Instance()->aplyhover();
    //Engine2D->draw();
    //Engine2D->checkbuton();
    Engine->EndDraw();
    Engine->resetClicked();

}

void PauseState::CLIN(){
    Singleton<Motor2D>::Instance()->CLINMenu();

    //Blackboard::ClearGlobalBlackboard();
    //Manager->clin();
    //world->clear();
    //EventSystem->clin();
}
