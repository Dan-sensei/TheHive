#ifndef _GAME_H
#define _GAME_H

class TMotorTAG;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>
#include <GameEngine/Clock.hpp>
#include "States/State.hpp"
#include <ComponentArch/Components/CCamera.hpp>


class Game : public State{
public:
    Game();
    Game(const Game &orig) = delete;
    ~Game();
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
    TMotorTAG* Engine;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    CCamera* MainCamera;

    gg::Clock MasterClock;
    double DeltaTime;
    double Tick; //PARA LA INTERPOLACION
    float Accumulator;

    gg::Color col;
};


#endif
