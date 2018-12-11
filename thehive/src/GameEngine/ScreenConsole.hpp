#ifndef SCREENCONSOLE_H
#define SCREENCONSOLE_H

#include <irrlicht/irrlicht.h>
#include <string>
#include "Singleton.hpp"
#include "Util.hpp"
#include <list>
#include <map>
#include "EventRec.hpp"


class GameEngine;

class ScreenConsole{
    friend class Singleton<ScreenConsole>;
    friend class GameEngine;
    public:
        void setprogress(int hab,float _prog);
        void setvida(float _vida);
        void setbullet(int tipo,int balas);
        void DisplayDebug();
        void DisplayHUD();
        void DisplayMenu();

        void CLIN();
        void InitHUD();
        void InitMenu();

        void AddTextToBuffer(const std::string &Text, const gg::Color &color);
        void AddImage(std::string palabra,std::string source  ,float _posx,float _posy,float _width,float _height);
    private:
        float porc_alto(float x);
        float porc_ancho(float x);

        int balaP;
        int balaS;
        float vida;
        float perc;
        float perc2;
        float perc3;
        float ancho;
        float alto;
        ScreenConsole();
        EventRec* eventManager;

        ScreenConsole(const ScreenConsole &orig) = delete;

        static irr::IrrlichtDevice* IrrlichtDevice;
        irr::gui::IGUIFont* font;
        struct BufferText{
            BufferText(const std::string &_Text, const gg::Color &_Color);
            std::string Text;
            gg::Color Color;
        };
        struct ImageHUD{
            ImageHUD(irr::video::ITexture* _texture,float _posx,float _posy,float _width,float _height);
            irr::video::ITexture* texture;
            float posx;
            float posy;
            float width;
            float height;
        };
        std::list<BufferText> BUFFER;
        std::map <std::string,ImageHUD>IMAGE_BUFFER;
};


namespace gg{
    void cout (const std::string &Text, const gg::Color &color = Color());
    void cout (const gg::Vector3f &Vector, const gg::Color &color = Color());
};

#endif
