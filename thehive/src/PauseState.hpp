#ifndef _PAUSESTATE_H
#define _PAUSESTATE_H

#include <Omicron/Omicron.hpp>
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

//#include <iostream>
#include "States/State.hpp"
#include <Omicron/SkyBox.hpp>
#include <Omicron/2D/GUIController.hpp>
#include <FMOD/SoundSystem.hpp>

class PauseState : public State{
public:
    PauseState();
    PauseState(const PauseState &orig) = delete;
    ~PauseState();
    //void update();
    //void RUN();
    virtual void CLIN();
    virtual void Init();
    virtual void Update();
    virtual void Resume();
    virtual void Pause() { }

    /*

    virtual void HandleInput() = 0;
    virtual void Draw(float dt) = 0;

    virtual void Pause() { }
    virtual void Resume() { }

    */

private:
    Omicron* Engine;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    GUIController* _GUIController;
    SkyBox sky;

    SoundSystem* SS;


};


#endif
