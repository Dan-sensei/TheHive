#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <string>
#include <irrlicht/irrlicht.h>

class Material {
    friend class Model;
    friend class GameEngine;
    public:
        Material();
        Material(const std::string &path);
        Material(const Material &orig);
        ~Material();

        void setTexture(const std::string &path);
        irr::video::SMaterial mMaterial;
    private:

        static irr::video::IVideoDriver* driver;
};


#endif
