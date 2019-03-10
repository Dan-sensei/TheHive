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


#include "SurrealEngine/SurrealEngine.hpp"


#include <GameEngine/EnumButtonType.hpp>


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
        void setprogress(int hab,float _prog);
        void setvida(float _vida);
        void setbullet(int,int,int);
        void setVolDialogo(int _vol);
        void setVolEffect(int _vol);
        void setVolMusic(int _vol);
        //void DisplayDebug();
        void DisplayHUD();

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
        Boton2D* addButton(float x, float y, float w,float h,EnumButtonType id,std::string imagenP,std::string imagenS,std::string texto,bool focus=false,glm::vec4 _color=glm::vec4(0,75/250.0,0,1));
        void addText(float x, float y,const std::string &Name,glm::vec4 _color=glm::vec4(1,0,0,1),float tam=20);
        Cuadrado2D* addRect(float x, float y,float w, float h);
        int checkbuton();
        void aplyhover();
    private:
        //nuevo
        std::vector<Cuadrado2D*> RECTANGULOS;
        SurrealEngine* motor;
        std::vector<Boton2D*> BOTONES;
        std::vector<Texto2D*> TEXT;
        //std::vector<Imagen2D*> IMAGENES;
        std::vector<std::pair<std::string,Imagen2D*>> IMAGENES;
        std::map<std::string,void(Motor2D::*)(Imagen2D*)> mapHudFunctions;




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







        void HUD_hability1(Imagen2D*);
        void HUD_hability2(Imagen2D*);
        void HUD_hability3(Imagen2D*);
        void HUD_vida(Imagen2D*);
        void HUD_arma0(Imagen2D*);
        void HUD_arma1(Imagen2D*);      // Principal
        std::string  BoolToString(bool b);

};
namespace gg{
    void cout (const std::string &Text, const gg::Color &color = Color());
    void cout (const glm::vec3 &Vector, const gg::Color &color = Color());
};

#endif
