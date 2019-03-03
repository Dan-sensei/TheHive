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

        void setPosition(const glm::vec3 &newPosition);
        void setRotation(const glm::vec3 &newRotation);

        glm::vec3 getPosition();
        glm::vec3 getRotation();

        void setTarget(const glm::vec3 &target);
        glm::vec3 getTarget();

        void updateAbsolutePosition();
        void bindTargetAndRotation(bool);

    private:
        irr::scene::ICameraSceneNode* mCamera;
};

#endif
