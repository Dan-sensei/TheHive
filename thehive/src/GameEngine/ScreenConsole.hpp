#ifndef SCREENCONSOLE_H
#define SCREENCONSOLE_H

#include <irrlicht/irrlicht.h>
#include <string>
#include "Singleton.hpp"
#include "Util.hpp"
#include <list>
#include <map>

class GameEngine;

class ScreenConsole{
    friend class Singleton<ScreenConsole>;
    friend class GameEngine;
    public:
        void DisplayDebug();
        void AddTextToBuffer(const std::string &Text, const gg::Color &color);
        void AddImage(std::string palabra,std::string source  ,float _posx,float _posy);

    private:
        ScreenConsole();
        ScreenConsole(const ScreenConsole &orig) = delete;

        static irr::IrrlichtDevice* IrrlichtDevice;
        irr::gui::IGUIFont* font;
        struct BufferText{
            BufferText(const std::string &_Text, const gg::Color &_Color);
            std::string Text;
            gg::Color Color;
        };
        struct ImageHUD{
            ImageHUD(irr::video::ITexture* _texture,float _posx,float _posy);
            irr::video::ITexture* texture;
            float posx;
            float posy;
        };
        std::list<BufferText> BUFFER;
        std::map <std::string,ImageHUD>IMAGE_BUFFER;
        
};


namespace gg{
    void cout (const std::string &Text, const gg::Color &color = Color());
    void cout (const gg::Vector3f &Vector, const gg::Color &color = Color());
};

#endif
