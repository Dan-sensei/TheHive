#include "GameEngine.hpp"

GameEngine::GameEngine()
:lastFPS(-1)
{

}

GameEngine::~GameEngine(){

}

//  ---
//  Initializes Irrlicht stuff
//==================================================================================
void GameEngine::Starto(){
    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080));
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
}

//  ---
//  Draws the complete scene. If the windows is not active, CPU usage is decreased
//==================================================================================
void GameEngine::Dro(){
    if (device->isWindowActive())
    {
        driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
        smgr->drawAll();
        driver->endScene();
    }
    else
        device->yield();
}

//  ---
//  Returns true if the windows is open
//==================================================================================
bool GameEngine::isWindowOpen(){
    return device->run();
}

//  ---
//  Display de FPS number on the toolbar
//==================================================================================
void GameEngine::DisplayFPS(){
    int fps = driver->getFPS();

    if (lastFPS != fps) {
        irr::core::stringw str = L"Irrlicht Engine - Quake 3 Map example [";
        str += driver->getName();
        str += "] FPS:";
        str += fps;

        device->setWindowCaption(str.c_str());
        lastFPS = fps;
    }
}

//  ---
//  Opens a compressed level
//==================================================================================
void GameEngine::openScene(std::string path){
    device->getFileSystem()->addFileArchive(path.c_str());
}

//  ---
//  Loads mesh. In this case, is the complete map
//==================================================================================
void GameEngine::loadMesh(std::string path){
    irr::scene::IAnimatedMesh* mesh = smgr->getMesh(path.c_str());
    irr::scene::ISceneNode* node = 0;
    if (mesh)   node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
}

//  ---
//  Hides or displays the cursor
//==================================================================================
void GameEngine::HideCursor(bool flag){
    device->getCursorControl()->setVisible(!flag);
}

//  ---
//  Adds a camera to the scene
//==================================================================================
void GameEngine::addCamera(){
    smgr->addCameraSceneNodeFPS();
}

//  ---
//  Cleans game engine stuff
//==================================================================================
void GameEngine::clean(){
    device->drop();
}
