#include <iostream>
#include "Singleton.hpp"
#include <irrlicht/irrlicht.h>

int main(int argc, char const *argv[]) {

    irr::IrrlichtDevice *device =
        irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080));

    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();

    device->getFileSystem()->addFileArchive("assets/Maps/tabd2map01/tabd2map01.pk3");

    irr::scene::IAnimatedMesh* mesh = smgr->getMesh("tabd2map01.bsp");
    irr::scene::ISceneNode* node = 0;

    if (mesh)   node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);

    if (node)
        node->setPosition(irr::core::vector3df(-1300,-144,-1249));

        smgr->addCameraSceneNodeFPS();
        device->getCursorControl()->setVisible(false);

    int lastFPS = -1;

    while(device->run())
    {
        if (device->isWindowActive())
        {
            driver->beginScene(true, true, irr::video::SColor(255,200,200,200));
            smgr->drawAll();
            driver->endScene();

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
        else
            device->yield();
    }

    device->drop();

    return 0;
}
