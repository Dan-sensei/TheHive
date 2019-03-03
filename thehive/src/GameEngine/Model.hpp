#ifndef _MODEL_H
#define _MODEL_H

#include <irrlicht/irrlicht.h>
#include "Util.hpp"
#include "Material.hpp"

class Model{
    friend class GameEngine;
    public:
        Model();
        Model(const Model &orig);
        ~Model();

        //  ---
        //  Sets the camera position
        //=============================================================
        void setPosition(const glm::vec3 &newPosition);
        void setRotation(const glm::vec3 &newRotation);

        //  ---
        //  Returns the position of the camera
        //=============================================================
        glm::vec3 getPosition();
        glm::vec3 getRotation();
        glm::vec3 getScale();

        //  ---
        //  We assign the material to the model
        //=============================================================
        void assignMaterial(const Material &mat);

    private:
        irr::scene::IAnimatedMeshSceneNode* mModel;
};

#endif
