#include "MenuState.hpp"

//#include <iostream>
#include <cstdint>
#include <string>
#include <stack>

#include "ComponentArch/ObjectManager.hpp"
#include "Singleton.hpp"

#include <Omicron/2D/Motor2D.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <States/StateMachine.hpp>


#define MOVEMENT_SPEED 1.f


MenuState::MenuState(){
    Engine = Singleton<Omicron>::Instance();
    cont = Singleton<GUIController>::Instance();
    EventSystem = Singleton<CTriggerSystem>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    Engine->HideCursor(false);
}

MenuState::~MenuState(){
    CLIN();
}

void MenuState::Init(){
    Singleton<Motor2D>::Instance()->InitMenu();
    Engine->HideCursor(false);

    cont->musicaMenuPlay();

    //musica_menu->play();

    //Engine->createCamera(glm::vec3(0, 30, 30), glm::vec3(0, 0, 0));
}
void MenuState::Resume() {
    Singleton<Motor2D>::Instance()->InitMenu();
    Engine->HideCursor(false);

    // cont->musicaMenuPause(false);

}
//void MenuState::submenu(){
//    CLIN();

//}
void MenuState::Update(){
    Engine->PollEvents();

    Engine->BeginDraw();
    cont->update();
    SS->update();
    //Singleton<Motor2D>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    Singleton<Motor2D>::Instance()->draw();
    Singleton<Motor2D>::Instance()->checkbuton();
    Singleton<Motor2D>::Instance()->aplyhover();
    //Engine2D->draw();
    //Engine2D->checkbuton();

    Engine->EndDraw();
    Engine->resetClickVariable();
}

void MenuState::CLIN(){
    Singleton<Motor2D>::Instance()->CLINMenu();
    cont->musicaMenuStop();
    //EventSystem->clin();
}
//
// void MenuState::Pause(){
//   cont->musicaMenuPause(true);
// }
