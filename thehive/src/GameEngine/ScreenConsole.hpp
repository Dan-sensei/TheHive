#ifndef SCREENCONSOLE_H
#define SCREENCONSOLE_H

#include <irrlicht/irrlicht.h>
#include <string>
#include "Singleton.hpp"
#include "Util.hpp"
#include <list>

class GameEngine;

class ScreenConsole{
    friend class Singleton<ScreenConsole>;
    friend class GameEngine;
    public:
        void DisplayDebug();
        void AddTextToBuffer(const std::string &Text, const gg::Color &color);
    private:
        ScreenConsole();
        ScreenConsole(const ScreenConsole &orig) = delete;

        static irr::IrrlichtDevice* IrrlichtDevice;
        struct BufferText{
            BufferText(const std::string &_Text, const gg::Color &_Color);
            std::string Text;
            gg::Color Color;
        };
        std::list<BufferText> BUFFER;
};


namespace gg{
    void cout (const std::string &Text, const gg::Color &color = Color());
};

#endif