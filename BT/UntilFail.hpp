#ifndef UntilFail_H
#define UntilFail_H

#include <iostream>

#include "decorator.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//
class UntilFail : public decorator{
public:
 Status update();

};



#endif /* DECORATOR_H */
