#ifndef Repetidor_H
#define Repetidor_H

#include <iostream>

#include "decorator.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//
class Repetidor : public decorator{
public:

 Status update();
 Repetidor(behavior* _m_pChild,float cont);

 void onInitialize();
private:
  float contador;
  float contador_max;

};



#endif /* DECORATOR_H */
