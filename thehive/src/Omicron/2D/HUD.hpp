#ifndef HUD_HPP
#define HUD_HPP

#include <iostream>
#include <Singleton.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Omicron/Shader.hpp>
#include <Omicron/AssetManager.hpp>
#include <Omicron/2D/Texto2D.hpp>
#include <Omicron/2D/Cuadrado2D.hpp>

class Omicron;
template <typename T>
class Singleton;

class HUD {
    friend class Singleton<HUD>;
    public:
        ~HUD();

        void initHUD(unsigned int SW, unsigned int SH, unsigned int TEX, Shader* _SHADER);
        void draw();

        void set_TL_CD(const float &cd);
        void set_TR_CD(const float &cd);
        void set_BM_CD(const float &cd);

        void setPrimaryBullets(const int &n);
        void setPrimaryChamber(const int &n);
        void setSecondaryBullets(const int &n);
        void setSecondaryChamber(const int &n);

        void setPrimaryImg(const unsigned int &idP, const unsigned int &idS);
        void setSecondaryImg(const unsigned int &idP, const unsigned int &idS);

        void changeHUDWeapon();
        void aim(const uint8_t &s);
        void setHealthBarPc(const float &pc);

        void setOmicron();
        void setFPS(int __FPS);
        void setDRAWNOBJECTS(int __DRAW);
        void setOclusion(bool O);

    private:
        HUD();
        HUD(const HUD &orig) = delete;

        Omicron* Engine;

        bool INIT;
        float ALPHA;

        unsigned int    VAO,VAO_2;
        unsigned int    VBO,VBO_2;
        unsigned int    EBO,EBO_2;
        unsigned int    IndexBuffer;
        unsigned int    textureID;

        unsigned int    crucetaG;
        unsigned int    crucetaP;
        unsigned int    actualCruceta;

        Shader          *SHADER;

        Texto2D TEXT_PrimaryBullets;
        Texto2D TEXT_PrimaryChamber;
        Texto2D TEXT_SecondaryBullets;
        Texto2D TEXT_SecondaryChamber;

        Cuadrado2D   HAB_TL;
        Cuadrado2D   HAB_TR;
        Cuadrado2D   HAB_BM;

        Cuadrado2D   HEALTH_BAR;

        unsigned int IMG_PrimaryW_P;
        unsigned int IMG_PrimaryW_S;
        unsigned int IMG_SecondaryW_P;
        unsigned int IMG_SecondaryW_S;
        unsigned int IMG_Actual_P;
        unsigned int IMG_Actual_S;

        Texto2D FPS;
        Texto2D DRAWN_OBJECTS;
        Texto2D OCLUSIONES;

        int FPS_;
        int DRAWN_OBJECTS_;
        bool OCC;

        void drawHUDItem(const float &_ZINDEX, const unsigned int &_IMG, const unsigned int &_VAO, const float &_ALPHA);
};
#endif
