#ifndef SCREENCONSOLE_H
#define SCREENCONSOLE_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <vector>


#include <irrlicht/irrlicht.h>
#include "Singleton.hpp"
#include "Util.hpp"

class GameEngine;

class ScreenConsole{
    friend class Singleton<ScreenConsole>;
    friend class GameEngine;
    public:
        void setprogress(int hab,float _prog);
        void setvida(float _vida);
        void setbullet(int tipo,int balas);
        void setVolDialogo(int _vol);
        void setVolEffect(int _vol);
        void setVolMusic(int _vol);
        void DisplayDebug();
        void DisplayHUD();
        void DisplayMenu();

        void CLINNormal();
        void CLINMenu();
        void InitHUD();
        int InitMenu();
        int InitMenu2();
        int InitMenu3();
        int InitMenu4();
        int InitMenu5();
        int InitMenu6();
        int InitMenu7();
        int InitPause();
        //int InitPause2();
        //int InitPause3();
        //int InitPause4();
        //int InitPause5();


        void AddTextToBuffer(const std::string &Text, const gg::Color &color);
        void AddStaticTextToBuffer(int x,int y, std::string Text,  gg::Color color);
        void AddImage(std::string palabra,std::string source  ,float _posx,float _posy,float _width,float _height);
        void addButton(float x, float y, float w,float h,int id,std::string texto,bool focus=false);
        int Pulsarboton(int but);
    private:
        float porc_alto(float x);
        float porc_ancho(float x);

        int VolDialogo;
        int VolEffect;
        int VolMusic;
        int balaP;
        int balaS;
        float vida;
        float perc;
        float perc2;
        float perc3;
        float ancho;
        float alto;

        ScreenConsole();

        ScreenConsole(const ScreenConsole &orig) = delete;

        static irr::IrrlichtDevice* IrrlichtDevice;
        irr::gui::IGUIFont* font;
        irr::video::IVideoDriver* driver;

        struct BufferText{
            BufferText(const std::string &_Text, const gg::Color &_Color);
            std::string Text;
            gg::Color Color;
        };
        struct StaticText{
            StaticText(float,float , std::string _Text,gg::Color _Color);
            std::string Text;
            gg::Color Color;
            float posx;
            float posy;
        };
        struct ImageHUD{
            ImageHUD(
                irr::video::ITexture* _texture,
                float _posx,
                float _posy,
                float _width,
                float _height
            );
            irr::video::ITexture* texture;
            float posx;
            float posy;
            float width;
            float height;
        };

        std::list<BufferText> BUFFER;

        std::vector<std::pair<std::string,ImageHUD>> IMAGE_BUFFER;
        std::map<std::string,void(ScreenConsole::*)(ImageHUD&)> mapHudFunctions;
        void HUD_hability1(ImageHUD&);
        void HUD_hability2(ImageHUD&);
        void HUD_hability3(ImageHUD&);
        void HUD_vida(ImageHUD&);
        void HUD_arma0(ImageHUD&);
        void HUD_arma1(ImageHUD&);      // Principal
        std::vector<irr::gui::IGUIButton*> Botones;
        std::vector<StaticText> TEXT_BUFFER;

};


namespace gg{
    void cout (const std::string &Text, const gg::Color &color = Color());
    void cout (const gg::Vector3f &Vector, const gg::Color &color = Color());
};

#endif
