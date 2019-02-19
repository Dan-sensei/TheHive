#ifndef _MENUSTATE_H
#define _MENUSTATE_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>
#include "States/State.hpp"
#include "GameEngine/GUIController.hpp"

#include <FMOD/SoundSystem.hpp>
#include <FMOD/SoundEvent.hpp>

class MenuState : public State{
public:
    MenuState();
    MenuState(const MenuState &orig) = delete;
    ~MenuState();
    //void update();
    //void RUN();
    virtual void CLIN();
    virtual void Init();
    virtual void Update();
    virtual void Resume();

    /*

    virtual void HandleInput() = 0;
    virtual void Draw(float dt) = 0;

    virtual void Pause() { }
    virtual void Resume() { }

    */

private:
    GameEngine* Engine;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    GUIController cont;

    SoundEvent*  s_menu;
    SoundSystem* SS;

};


#endif
