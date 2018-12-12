#ifndef _PAUSESTATE_H
#define _PAUSESTATE_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>
#include "States/State.hpp"
#include "GameEngine/GUIController.hpp"

class PauseState : public State{
public:
    PauseState();
    PauseState(const PauseState &orig) = delete;
    ~PauseState();
    //void update();
    //void RUN();
    virtual void CLIN();
    virtual void Init();
    virtual void Update(float dt);
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

};


#endif
