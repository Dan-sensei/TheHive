#ifndef _GAME_H
#define _GAME_H

class SurrealEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

class AIDirector;

//#include <iostream>
#include <SurrealEngine/Clock.hpp>
#include "States/State.hpp"
#include <ComponentArch/Components/CCamera.hpp>
#include <SurrealEngine/SkyBox.hpp>
#include <FMOD/SoundSystem.hpp>

class Motor2D;
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
    SurrealEngine* Engine;
    Motor2D* Engine2D;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    CCamera* MainCamera;
    AIDirector* Director;
    SoundSystem* soundSys;

    gg::Clock MasterClock;
    double DeltaTime;
    double Tick; //PARA LA INTERPOLACION
    float Accumulator;

    gg::Color col;
    TNodo* luz;
    CTransform* playerpos;
    SkyBox sky;
};


#endif
