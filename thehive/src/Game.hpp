#ifndef _GAME_H
#define _GAME_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

class AIDirector;

#include <iostream>
#include <GameEngine/Clock.hpp>
#include "States/State.hpp"
#include <ComponentArch/Components/CCamera.hpp>
#include <FMOD/SoundSystem.hpp>


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
    GameEngine* Engine;
    CTriggerSystem* EventSystem;
    ObjectManager* Manager;
    ggDynWorld* world;
    CCamera* MainCamera;
    AIDirector* Director;
    SoundSystem* soundSys;
    SoundEvent* s_basica;
    SoundEvent* s_accion;

    gg::Clock MasterClock;
    double DeltaTime;
    double Tick; //PARA LA INTERPOLACION
    float Accumulator;

    uint UPDATE;
    uint DRO;
};


#endif
