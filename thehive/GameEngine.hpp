#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H

#include <string>
#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/Keycodes.h>
#include <irrlicht/SKeyMap.h>

#include "ENode.hpp"
#include "Camera.hpp"
#include "Util.hpp"
#include "KEYCODES.hpp"
#include "EventListener.hpp"
#include "Model.hpp"
#include "Material.hpp"

class GameEngine{
public:
    GameEngine();
    GameEngine(const GameEngine& orig) = delete;
    ~GameEngine();

    void Starto();
    void Dro();
    bool isWindowOpen();
    void DisplayFPS();

    void openScene(std::string path);
    void loadMesh(ENode*);
    void pollEvents();

    void HideCursor(bool flag);

    Camera createCamera(const gg::Vector3f &position = {0,0,0}, const gg::Vector3f &direction = {0,0,0});
    Model createModel(const std::string &path, const gg::Vector3f &position = {0,0,0});

    bool key(irr::EKEY_CODE keycode);

    void clean();

private:
    irr::IrrlichtDevice *device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* smgr;

    int lastFPS;
    EventListener listener;
};
#endif
