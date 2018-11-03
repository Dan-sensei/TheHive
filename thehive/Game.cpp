#include "Game.hpp"
#include "Camera.hpp"
#include "Util.hpp"

#define MOVEMENT_SPEED 1.f

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

    //ENode *mierdote = new ENode("assets/Models/obradearte/algo.obj", "assets/Models/obradearte/prueba1.png");
    //engine.loadMesh(mierdote);

    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");
    Model tioPablomanesQueNoEstaTanMal = engine.createModel("assets/Models/obradearte/algo.obj");

    tioPablomanesQueNoEstaTanMal.assignMaterial(moradoDeLos80);

    Camera camera = engine.createCamera(gg::Vector3f(50, 0, -100), gg::Vector3f(0, 0, 50));
    //camera.setPosition(gg::Vector3f(-50, 0, 100));
    //camera.setTarget(gg::Vector3f(0, 0, 50));

    while(engine.isWindowOpen()) {

        gg::Vector3f nextPosition = tioPablomanesQueNoEstaTanMal.getPosition();

        if(engine.key(gg::GG_W))
            nextPosition.Z += MOVEMENT_SPEED;
        else if(engine.key(gg::GG_S))
            nextPosition.Z -= MOVEMENT_SPEED;

        if(engine.key(gg::GG_A))
            nextPosition.X -= MOVEMENT_SPEED;
        else if(engine.key(gg::GG_D))
            nextPosition.X += MOVEMENT_SPEED;

        tioPablomanesQueNoEstaTanMal.setPosition(nextPosition);

        engine.Dro();
        engine.DisplayFPS();
    }
}

void Game::CLIN(){
    engine.clean();
}
