#include "PopState.hpp"

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



PopState::PopState()
{
    _GUIController = Singleton<GUIController>::Instance();
    Engine = Singleton<Omicron>::Instance();
    SS = Singleton<SoundSystem>::Instance();
    cont=0;
}

PopState::~PopState(){
    CLIN();
}
void PopState::Addim(std::string im){
    imagenes.push_back(im);
}

void PopState::Init(){
    Engine->HideCursor(false);
    //Singleton<Motor2D>::Instance()->InitPause();
    //Singleton<Motor2D>::Instance()->InitPause();
    Singleton<Motor2D>::Instance()->pintarImagen(imagenes.front());

    //_GUIController->musicaMenuPlay();
    //Engine->createCamera(glm::vec3(0, /* message */30, 30), glm::vec3(0, 0, 0));
}
void PopState::siguiente(){
    cont++;
    if(cont<imagenes.size()){
        Singleton<Motor2D>::Instance()->pintarImagen(imagenes.at(cont));
    }
    else{
        Singleton<StateMachine>::Instance()->RemoveStates();
    }
}
void PopState::Resume(){
    Init();
}

//void PopState::submenu(){
//    CLIN();
//}

void PopState::Update(){

    Engine->PollEvents();
    if(Engine->key(gg::X, true))  {
        siguiente();

    }
    Engine->BeginDraw();
    Engine->draw();
    _GUIController->update();

    //Singleton<Motor2D>::Instance()->DisplayMenu();
    //Singleton<StateMachine>::Instance()->AddState(new GameState());
    //Singleton<Motor2D>::Instance()->draw();
    Singleton<Motor2D>::Instance()->DisplayHUD();
    //Singleton<Motor2D>::Instance()->checkbuton();
    //Singleton<Motor2D>::Instance()->aplyhover();
    //Engine2D->draw();
    //Engine2D->checkbuton();
    Engine->EndDraw();
    //Engine->resetClickVariable();

    SS->update();

}

void PopState::CLIN(){
    Singleton<Motor2D>::Instance()->clinpopup();
    Singleton<Motor2D>::Instance()->CLINMenu();
    //_GUIController->musicaMenuStop();
}
