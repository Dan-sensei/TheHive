#ifndef _GAME_H
#define _GAME_H

class Omicron;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

class AIDirector;

//#include <iostream>
#include <Omicron/Clock.hpp>
#include "States/State.hpp"
#include <ComponentArch/Components/CCamera.hpp>
#include <Omicron/SkyBox.hpp>
#include <FMOD/SoundSystem.hpp>
#include <Omicron/NatureGenerator.hpp>
#include <Omicron/2D/GUIController.hpp>
#include <FMOD/SonidoNormal.hpp>

class Motor2D;
class Game : public State{
public:
    Game();
    // virtual void Pause() { }
    Game(const Game &orig) = delete;
    virtual ~Game();
    //void update();
    //void RUN();
    virtual void CLIN();
    virtual void Init();
    virtual void Update();
    virtual void Resume();
    virtual void Pause();

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
    CCamera* MainCamera;
    AIDirector* Director;
    SoundSystem* soundSys;
    SoundEvent* dialogoInicial;
    GUIController* cont;

    gg::Clock MasterClock;
    double DeltaTime;
    double Tick; //PARA LA INTERPOLACION
    float Accumulator;

    gg::Color col;
    StandardNode* luz;
    CTransform* playerpos;

    //SkyBox sky;
    NatureGenerator nat;
    ParticleSystem* PS;

    void FirstUpdate();
    void SecondUpdate();
    void NormalUpdate();
    void (Game::*UPD)();
};


#endif
