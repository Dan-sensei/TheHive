#ifndef LETRA2DMANAHER_H
#define LETRA2DMANAHER_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "TNodo.hpp"
#include "Letra2D.hpp"
#include "Singleton.hpp"


class Letra2DManager {
    friend class Singleton<Letra2DManager>;

    public:
        //Letra2DManager();
        Letra2DManager();

        Letra2DManager(const Letra2DManager &orig) = delete;
        ~Letra2DManager();

        Letra2D* getChar(char letra);

        float ancho;
        float alto;


    private:
        Letra2D* letraux;
        std::map<char,void(Letra2D::*)()> mapHudFunctions;
        //using pFunc = void(Action::*)();


};

#endif
