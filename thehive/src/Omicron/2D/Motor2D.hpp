#ifndef MOTOR2D_H
#define MOTOR2D_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <vector>


#include <Singleton.hpp>
#include <Util.hpp>

#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>

#include <Omicron/2D/EnumButtonType.hpp>
#include <Omicron/2D/ImageButton.hpp>

class Omicron;
class Boton2D;
class Imagen2D;
class Cuadrado2D;
class GameEngine;
class Texto2D;

class Motor2D{
    friend class Singleton<Motor2D>;
    friend class GameEngine;
    public:
        ~Motor2D();
        void pintarTexto(int nlineas,std::string texto[]);
        void CLINTexto();
        void setprogress(int hab,float _prog);
        void setvida(float _vida);
        void setbullet(int,int,int);
        void setVolDialogo(int _vol);
        void setVolEffect(int _vol);
        void setVolMusic(int _vol);
        //void DisplayDebug();
        void clinpopup();

        void CLINNormal();
        void CLINMenu();
        void InitHUD();
        int InitMenu();
        int InitMenu2();
        int InitMenu3();
        int InitOptions();
        int InitMenu5();
        int InitMenu6();
        int InitMenu7();
        int InitPause();
        int InitAIDebug(int id);

        //int InitPause2();
        //int InitPause3();
        //int InitPause4();
        //int InitPause5();
        void draw();
        void colorMute(EnumButtonType);

        //void AddTextToBuffer(const std::string &Text, const gg::Color &color);
        //void AddStaticTextToBuffer(int x,int y, std::string Text,  gg::Color color);

        //Imagen2D* AddImage(std::string source  ,float _posx,float _posy,float _width,float _height);
        //Boton2D* addButton(float x, float y, float w,float h,EnumButtonType id,std::string imagenP,std::string imagenS,std::string texto,bool focus=false,glm::vec4 _color=glm::vec4(0,0,0,1));
        void addText(float x, float y,const std::string &Name,glm::vec4 _color=glm::vec4(0,0,0,1),float tam=20);
        Cuadrado2D* addRect(float x, float y,float w, float h);
        int checkbuton();
        void aplyhover();
    private:
        bool pop;
        Imagen2D* POUP;
        SoundSystem* SS;

        Omicron* motor;
        SoundEvent* s_hover;
        //nuevo
        std::vector<Cuadrado2D> RECTANGULOS;
        std::vector<ImageButton> BOTONES;
        std::vector<Imagen2D> IMAGENES;
        std::vector<Texto2D> TEXT;
        //std::vector<Imagen2D*> IMAGENES;
        //std::vector<std::pair<std::string,Imagen2D*>> IMAGENES;
        //td::vector<std::pair<std::string,Imagen2D*>> IMAGENES;
        //std::vector<void(Motor2D::*)(Imagen2D*)> mapHudFunctions;
        //using pGui = void(Motor2D::*)(Imagen2D*);
        //pGui mapHudFunctions[6];




        int VolDialogo;
        int VolEffect;
        int VolMusic;
        int balaP, balaP_TOT;
        int balaS, balaS_TOT;
        bool muteEffect, muteMusic, muteDialog;
        float vida;
        float perc;
        float perc2;
        float perc3;
        float ancho;
        float alto;



        Motor2D();

        Motor2D(const Motor2D &orig) = delete;



        std::string  BoolToString(bool b);

};

#endif
