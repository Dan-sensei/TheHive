#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <irrlicht/irrlicht.h>
#include <string>
#include <cstdint>

class Billboard{
    friend class GameEngine;
    public:
        Billboard();
        Billboard(const Billboard &orig);
        ~Billboard();

        void setText(const std::string &Text);
        void setColor(const uint8_t Color[4]);

    private:
        irr::scene::IBillboardTextSceneNode* billboard;

};

#endif