#ifndef _GAME_H
#define _GAME_H

class GameEngine;
class CTriggerSystem;

class ObjectManager;
class ggDynWorld;

#include <iostream>

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
};


#endif
