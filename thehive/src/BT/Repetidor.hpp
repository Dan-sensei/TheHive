#ifndef REPETIDOR_H
#define REPETIDOR_H

//#include <iostream>
#include "Decorator.hpp"

class Repetidor : public Decorator{
    public:
        void onInitialize();
        Status update();
        Repetidor(Behavior* _m_pChild,float cont);
    private:
        float contador;
        float contador_max;
};
#endif
