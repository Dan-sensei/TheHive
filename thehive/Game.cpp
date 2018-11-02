#include "Game.hpp"

Game::Game(){
    engine.Starto();
}

Game::~Game(){

}


void Game::RUN(){
    engine.openScene("assets/Maps/tabd2map01/tabd2map01.pk3");
    engine.loadMesh("tabd2map01.bsp");
    engine.HideCursor(true);
    engine.addCamera();

    while(engine.isWindowOpen()){
        engine.Dro();
        engine.DisplayFPS();
    }
}

void Game::CLIN(){
    engine.clean();
}
