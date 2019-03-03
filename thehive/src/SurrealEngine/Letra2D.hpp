#ifndef LETRA2D_H
#define LETRA2D_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "TNodo.hpp"

class Letra2D {
    public:
        //Letra2D();
        Letra2D();

        //Letra2D(const Letra2D &orig) = delete;
        ~Letra2D();


        float getX();
        float getW();
        float getY();
        float getH();

        float getTX();
        float getTW();
        float getTY();
        float getTH();

        void inita();
        void initb();
        void initc();
        void initd();
        void inite();
        void initf();
        void initg();
        void inith();
        void initi();
        void initj();
        void initk();
        void initl();
        void initm();
        void initn();
        void inito();
        void initp();
        void initq();
        void initr();
        void inits();
        void initt();
        void initu();
        void initv();
        void initw();
        void initx();
        void inity();
        void initz();

        void initA();
        void initB();
        void initC();
        void initD();
        void initE();
        void initF();
        void initG();
        void initH();
        void initI();
        void initJ();
        void initK();
        void initL();
        void initM();
        void initN();
        void initO();
        void initP();
        void initQ();
        void initR();
        void initS();
        void initT();
        void initU();
        void initV();
        void initW();
        void initX();
        void initY();
        void initZ();


        void resize(float alto);


        void init2();
    private:
        std::map<char,void(Letra2D::*)()> mapHudFunctions;
        //using pFunc = void(Action::*)();

            float X,Y,W,H;
            float TX,TY,TW,TH;
            float ratio;

};

#endif
