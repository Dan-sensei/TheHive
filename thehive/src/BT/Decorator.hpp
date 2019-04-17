#ifndef DECORATOR_H
#define DECORATOR_H

//#include <iostream>
#include "Behavior.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//
class Decorator : public Behavior {
    protected:
       Behavior* m_pChild;     // Comportamiento hijo
    public:
       Decorator(Behavior* _m_pChild);
       Decorator();
       virtual ~Decorator();
       // Sobreescribir los metodos de la interfaz
       //virtual Status update();
};
#endif
