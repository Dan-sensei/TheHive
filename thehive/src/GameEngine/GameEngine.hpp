#ifndef _GAMEENGINE_H
#define _GAMEENGINE_H

#include <string>
#include <iostream>
#include <irrlicht/irrlicht.h>
#include <irrlicht/Keycodes.h>
#include <irrlicht/SKeyMap.h>

#include "KEYCODES.hpp"
#include "ENode.hpp"
#include "Camera.hpp"
#include "Util.hpp"
#include "EventListener.hpp"
#include "Model.hpp"
#include "Material.hpp"
#include <Bullet/ggDynWorld.hpp>

template <typename T>
class Singleton;

class GameEngine{
    friend class Singleton<GameEngine>;
    public:
        ~GameEngine();

        void Starto();
        void Dro();
        bool isWindowOpen();
        void DisplayFPS();

        void openScene(std::string path);
        void loadMesh(ENode*);
        void pollEvents();

        void HideCursor(bool flag);

        //  ---
        //  Creates and returns a camera object. It optionally accepts a position
        //  and looking direction
        //==================================================================================
        void createCamera(const gg::Vector3f &position = {0,0,0}, const gg::Vector3f &direction = {0,0,0});
        Camera* getCamera();
        int getScreenWidth();
        int getScreenHeight();
        int getCursorX();
        int getCursorY();
        void setCursorPosition(int,int);

        void draw3DLine(const gg::Vector3f&, const gg::Vector3f&, const float[4]);

        //  ---
        //  Creates and returns a model object. It optionally accepts a position
        //==================================================================================
        void createModel(Model &model, const std::string &path, const gg::Vector3f &position = {0,0,0});

        bool key(gg::KEYCODES keyCode);

        void clean();

    private:
        GameEngine();
        GameEngine(const GameEngine &orig) = delete;
        void operator=(const GameEngine &orig) = delete;

        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver* driver;
        irr::scene::ISceneManager* smgr;

        int lastFPS;
        EventListener listener;
        Camera G_Camera;
    };
#endif
