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
//  Adds a camera to the scene
//==================================================================================
void GameEngine::addCamera(){
    irr::SKeyMap keyMap[8];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = irr::KEY_UP;
    keyMap[1].Action = irr::EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_W;

    keyMap[2].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = irr::KEY_DOWN;
    keyMap[3].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = irr::KEY_KEY_S;

    keyMap[4].Action = irr::EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = irr::KEY_LEFT;
    keyMap[5].Action = irr::EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = irr::KEY_KEY_A;

    keyMap[6].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = irr::KEY_RIGHT;
    keyMap[7].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[7].KeyCode = irr::KEY_KEY_D;

    smgr->addCameraSceneNodeFPS(0, 100, 0.5, -1, keyMap, 8);


    // smgr->addCameraSceneNode();

}

//  ---
//  Cleans game engine stuff
//==================================================================================
void GameEngine::clean(){
    device->drop();
}
