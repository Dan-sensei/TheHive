#ifndef MOTOR2D_H
#define MOTOR2D_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <vector>


#include <irrlicht/irrlicht.h>
#include "Singleton.hpp"
#include "Util.hpp"


#include "SurrealEngine/TMotorTAG.hpp"
#include "SurrealEngine/Imagen2D.hpp"
#include "SurrealEngine/Boton2D.hpp"
#include "SurrealEngine/Cuadrado2D.hpp"

#include <GameEngine/EnumButtonType.hpp>



class GameEngine;

class Motor2D{
    friend class Singleton<Motor2D>;
    friend class GameEngine;
    public:
        void setprogress(int hab,float _prog);
        void setvida(float _vida);
        void setbullet(int,int,int);
        void setVolDialogo(int _vol);
        void setVolEffect(int _vol);
        void setVolMusic(int _vol);
        //void DisplayDebug();
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
        int InitAIDebug(int id);
        void prueba();

        //int InitPause2();
        //int InitPause3();
        //int InitPause4();
        //int InitPause5();
        void draw();


        //void AddTextToBuffer(const std::string &Text, const gg::Color &color);
        //void AddStaticTextToBuffer(int x,int y, std::string Text,  gg::Color color);
        void AddImage(std::string palabra,std::string source  ,float _posx,float _posy,float _width,float _height);
        void addButton(float x, float y, float w,float h,EnumButtonType id,std::string imagenP,std::string imagenS,std::string texto,bool focus=false);
        int Pulsarboton(int but);
        void addText(float x, float y,const std::string &Name,glm::vec4 _color=glm::vec4(0,0,0,1),float tam=0.1);
        int checkbuton();
        void aplyhover();
    private:
        //nuevo
        //std::vector<Cuadrado2D*> RECTANGULOS;
        TMotorTAG* motor;
        std::vector<Boton2D*> BOTONES;
        std::vector<Texto2D*> TEXT;
        //std::vector<Imagen2D*> IMAGENES;
        std::vector<std::pair<std::string,Imagen2D*>> IMAGENES;
        std::map<std::string,void(Motor2D::*)(Imagen2D*)> mapHudFunctions;



        float porc_alto(float x);
        float porc_ancho(float x);

        int VolDialogo;
        int VolEffect;
        int VolMusic;
        int balaP, balaP_TOT;
        int balaS, balaS_TOT;
        float vida;
        float perc;
        float perc2;
        float perc3;
        float ancho;
        float alto;

        Motor2D();

        Motor2D(const Motor2D &orig) = delete;

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


        std::list<BufferText> BUFFER;

        void HUD_hability1(Imagen2D*);
        void HUD_hability2(Imagen2D*);
        void HUD_hability3(Imagen2D*);
        void HUD_vida(Imagen2D*);
        void HUD_arma0(Imagen2D*);
        void HUD_arma1(Imagen2D*);      // Principal
        std::vector<irr::gui::IGUIButton*> Botones;
        std::vector<StaticText> TEXT_BUFFER;
        std::string  BoolToString(bool b);

};

#endif
