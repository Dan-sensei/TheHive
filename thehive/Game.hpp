#ifndef _GAME_H
#define _GAME_H

#include "GameEngine.hpp"

#include <iostream>

class Game{
public:
    Game();
    Game(const Game &orig) = delete;
    ~Game();

    void RUN();
    void CLIN();

private:
    GameEngine* engine;
};


#endif
