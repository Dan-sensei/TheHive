#ifndef _OPTIONSTATE_H
#define _OPTIONSTATE_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>
#include "States/State.hpp"
#include "GameEngine/GUIController.hpp"

#include <FMOD/SoundSystem.hpp>
#include <FMOD/SoundEvent.hpp>

class OptionState : public State{
public:
    OptionState();
    OptionState(const OptionState &orig) = delete;
    ~OptionState();
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

    SoundEvent*  s_aceptar;
    SoundSystem* SS;

};


#endif
