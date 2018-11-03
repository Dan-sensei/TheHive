#ifndef _CAMERA_H
#define _CAMERA_H

#include <irrlicht/irrlicht.h>
#include "Util.hpp"

class Camera{
    friend class GameEngine;
public:
    Camera();
    Camera(const Camera &orig);
    ~Camera();
    
    void setPosition(const gg::Vector3f &newPosition);
    void setTarget(const gg::Vector3f &target);
    gg::Vector3f getPosition();

private:
    irr::scene::ICameraSceneNode* mCamera;
};

#endif
