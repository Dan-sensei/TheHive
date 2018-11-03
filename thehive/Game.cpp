#include "Game.hpp"
#include "Camera.hpp"

Game::Game(){
    engine.Starto();
    engine.HideCursor(true);
}

Game::~Game(){

}

void Game::RUN(){
    // engine.openScene("assets/Maps/tabd2map01/tabd2map01.pk3");
    // engine.loadMesh("tabd2map01.bsp");
    // engine.loadMesh("assets/Models/obradearte/algo.obj");
    ENode *mierdote = new ENode("assets/Models/obradearte/algo.obj", "assets/Models/obradearte/prueba1.png");
    engine.loadMesh(mierdote);

    Camera camera = engine.createCamera(gg::Vector3f(-50, 0, 100), gg::Vector3f(0, 0, 50));
    //camera.setPosition(gg::Vector3f(-50, 0, 100));
    //camera.setTarget(gg::Vector3f(0, 0, 50));

    while(engine.isWindowOpen()){
        engine.Dro();
        engine.DisplayFPS();
    }
}

void Game::CLIN(){
    engine.clean();
}
