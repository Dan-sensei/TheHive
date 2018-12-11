#ifndef _GAMESTATE_H
#define _GAMESTATE_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>
#include "States/State.hpp"

class GameState : public State{
public:
    GameState();
    GameState(const GameState &orig) = delete;
    ~GameState();
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
};


#endif
