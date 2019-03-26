#ifndef _OPTIONSTATE_H
#define _OPTIONSTATE_H

#include <SurrealEngine/SurrealEngine.hpp>
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

//#include <iostream>
#include "States/State.hpp"
#include "GameEngine/GUIController.hpp"
#include <FMOD/SoundSystem.hpp>

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
    SurrealEngine* Engine;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    GUIController cont;

    SoundSystem* SS;

};


#endif
