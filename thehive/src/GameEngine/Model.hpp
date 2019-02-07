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
        void setPosition(const gg::Vector3f &newPosition);
        void setRotation(const gg::Vector3f &newRotation);

        //  ---
        //  Returns the position of the camera
        //=============================================================
        gg::Vector3f getPosition();
        gg::Vector3f getRotation();
        gg::Vector3f getScale();

        void setVisibility(bool flag);

        //  ---
        //  We assign the material to the model
        //=============================================================
        void assignMaterial(const Material &mat);

    private:
        irr::scene::IAnimatedMeshSceneNode* mModel;
};

#endif
