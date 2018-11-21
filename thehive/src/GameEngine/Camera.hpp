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
        void setRotation(const gg::Vector3f &newRotation);

        gg::Vector3f getPosition();
        gg::Vector3f getRotation();

        void setTarget(const gg::Vector3f &target);
        gg::Vector3f getTarget();

        void updateAbsolutePosition();
        void bindTargetAndRotation(bool);

    private:
        irr::scene::ICameraSceneNode* mCamera;
};

#endif
