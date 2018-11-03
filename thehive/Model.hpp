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

        void setPosition(const gg::Vector3f &newPosition);
        gg::Vector3f getPosition();

        void assignMaterial(const Material &mat);

    private:
        irr::scene::IAnimatedMeshSceneNode* mModel;
};

#endif
