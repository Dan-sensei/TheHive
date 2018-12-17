#ifndef _GAME_H
#define _GAME_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>
#include "States/State.hpp"

class Game : public State{
public:
    Game();
    Game(const Game &orig) = delete;
    ~Game();
    //void update();
    //void RUN();
    virtual void CLIN();
    virtual void Init();
    virtual void Update(float dt);
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
};


#endif
