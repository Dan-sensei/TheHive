#include "Game.hpp"

Game::Game(){
    engine.Starto();
}

Game::~Game(){

}

void Game::RUN(){
    // engine.openScene("assets/Maps/tabd2map01/tabd2map01.pk3");
    // engine.loadMesh("tabd2map01.bsp");
    // engine.loadMesh("assets/Models/obradearte/algo.obj");
    ENode *mierdote = new ENode("assets/Models/obradearte/algo.obj", "assets/Models/obradearte/prueba1.png");
    engine.loadMesh(mierdote);

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
