#ifndef _GAME_H
#define _GAME_H

class Omicron;
class CTriggerSystem;
class ObjectManager;
class ggDynWorld;

<<<<<<< HEAD
#include <FMOD/SoundSystem.hpp>
#include <iostream>
=======
class AIDirector;
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce

//#include <iostream>
#include <Omicron/Clock.hpp>
#include "States/State.hpp"
#include <ComponentArch/Components/CCamera.hpp>
#include <Omicron/SkyBox.hpp>
#include <FMOD/SoundSystem.hpp>
#include <Omicron/NatureGenerator.hpp>
#include <Omicron/2D/GUIController.hpp>

class Motor2D;
class Game : public State{
public:
    Game();
    // virtual void Pause() { }
    Game(const Game &orig) = delete;
    ~Game();
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
    Motor2D* Engine2D;
    CTriggerSystem* EventSystem;
<<<<<<< HEAD
    SoundSystem* soundSys;
=======
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
    ObjectManager* Manager;
    ggDynWorld* world;
    CCamera* MainCamera;
    AIDirector* Director;
    SoundSystem* soundSys;
    GUIController* cont;


    gg::Clock MasterClock;
    double DeltaTime;
    double Tick; //PARA LA INTERPOLACION
    float Accumulator;

    gg::Color col;
    TNodo* luz;
    CTransform* playerpos;

    SkyBox sky;
    NatureGenerator nat;
};


#endif
