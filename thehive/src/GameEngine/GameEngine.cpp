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
    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, &listener);
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    Material::driver = driver;
}

//  ---
//  Draws the complete scene. If the windows is not active, CPU usage is decreased
//==================================================================================
void GameEngine::Dro(){
    if (device->isWindowActive())
    {
        driver->beginScene(true, true, irr::video::SColor(255,255,255,255));
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
        irr::core::stringw str = "Irrlicht Engine - Quake 3 Map example [";
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
void GameEngine::loadMesh(ENode* node){
    // irr::scene::IAnimatedMesh* mesh = smgr->getMesh(path.c_str());
    // irr::scene::ISceneNode* node = 0;
    // if (mesh)   node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
    //
    // if (node){
    //     node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //     node->setMaterialTexture(0, driver->getTexture("assets/Models/obradearte/prueba1.png"));
    // }
    irr::scene::IAnimatedMesh* mesh = smgr->getMesh( node->getMPath().c_str() );
    node->setAnimatedMesh(mesh);
    node->setSceneNode(0);

    if(node->getAnimatedMesh())
        node->setSceneNode( smgr->addOctreeSceneNode(node->getAnimatedMesh()->getMesh(0), 0, -1, 1024) );

    if (node->getSceneNode() && node->getTPath()!="NO_PATH"){
        node->getSceneNode()->setMaterialFlag(irr::video::EMF_LIGHTING, false);

        node->getSceneNode()->setMaterialTexture(0, driver->getTexture( node->getTPath().c_str() ));
    }


}


//  ---
//  Hides or displays the cursor
//==================================================================================
void GameEngine::HideCursor(bool flag){
    device->getCursorControl()->setVisible(!flag);
}


//  ---
//  Adds a camera to the scene with optional initial coordinates
//==================================================================================
void GameEngine::createCamera(const gg::Vector3f &position /* = {0,0,0} */, const gg::Vector3f &direction /* = {0,0,0} */) {

    G_Camera.mCamera = smgr->addCameraSceneNode(
        0,
        irr::core::vector3df(position.X, position.Y, position.Z),
        irr::core::vector3df(direction.X, direction.Y, direction.Z)
    );

}

Camera* GameEngine::getCamera(){
    return &G_Camera;
}

int GameEngine::getScreenWidth(){
    return driver->getScreenSize().Width;
}

int GameEngine::getScreenHeight(){
    return driver->getScreenSize().Height;
}

int GameEngine::getCursorX(){
    return device->getCursorControl()->getPosition().X;
}

int GameEngine::getCursorY(){
    return device->getCursorControl()->getPosition().Y;
}

void GameEngine::setCursorPosition(int x, int y){
    device->getCursorControl()->setPosition(x, y);
}

//  ---
//  Adds a 3D model to the scene on the desired position or 0, 0, 0 by default
//==================================================================================
Model GameEngine::createModel(const std::string &path, const gg::Vector3f &position /* = {0,0,0} */) {

    Model newModel;
    newModel.mModel = smgr->addAnimatedMeshSceneNode(smgr->getMesh(path.c_str()));

    if(newModel.mModel){
        newModel.mModel->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        //newModel.mModel->setMD2Animation(scene::EMAT_STAND);
    }
    return newModel;
}

bool GameEngine::key(gg::KEYCODES keyCode){
    return listener.IsKeyDown(keyCode);
}

//  ---
//  Cleans game engine stuff
//==================================================================================
void GameEngine::clean(){
    device->drop();
}
