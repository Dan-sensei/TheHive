#include "PauseState.hpp"

#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include <Omicron/2D/Motor2D.hpp>

#include "Factory.hpp"
#include <States/StateMachine.hpp>



#define MOVEMENT_SPEED 1.f



PauseState::PauseState()
{
    _GUIController = Singleton<GUIController>::Instance();
    Engine = Singleton<Omicron>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    sky.init();
}

PauseState::~PauseState(){
    CLIN();
}

void PauseState::Init(){

    Engine->HideCursor(false);
    Singleton<Motor2D>::Instance()->InitPause();
    _GUIController->musicaMenuPlay();


    //Engine->createCamera(glm::vec3(0, /* message */30, 30), glm::vec3(0, 0, 0));
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
    _GUIController->update();
    //Singleton<Motor2D>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    sky.Draw();
    Singleton<Motor2D>::Instance()->draw();
    Singleton<Motor2D>::Instance()->checkbuton();
    Singleton<Motor2D>::Instance()->aplyhover();
    //Engine2D->draw();
    //Engine2D->checkbuton();
    Engine->EndDraw();
    Engine->resetClickVariable();

    SS->update();

}

void PauseState::CLIN(){
    Singleton<Motor2D>::Instance()->CLINMenu();
    _GUIController->musicaMenuStop();

    //Blackboard::ClearGlobalBlackboard();
    //Manager->clin();
    //world->clear();
}
