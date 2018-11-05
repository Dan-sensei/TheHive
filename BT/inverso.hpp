#ifndef INVERSO_H
#define INVERSO_H

#include <iostream>

#include "decorator.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//
class inverso : public decorator{
public:
 Status update();

};



#endif /* DECORATOR_H */
