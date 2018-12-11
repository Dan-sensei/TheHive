#ifndef _GAME_H
#define _GAME_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>
#include <GameEngine/Clock.hpp>

class Game{
public:
    Game();
    Game(const Game &orig) = delete;
    ~Game();

    void RUN();
    void CLIN();

private:
    GameEngine* Engine;
    CTriggerSystem* EventSystem;

    ObjectManager* Manager;
    ggDynWorld* world;

    gg::Clock MasterClock;
    double DeltaTime;
    double Tick; //PARA LA INTERPOLACION
    float Accumulator;
};


#endif
