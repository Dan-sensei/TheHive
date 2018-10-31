#ifndef DECORATOR_H
#define DECORATOR_H

#include <iostream>

#include "behavior.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//

class decorator : public behavior {
protected:
   behavior* m_pChild;     // Comportamiento hijo
public:
   decorator(behavior*);

   // Sobreescribir los metodos de la interfaz
   Status update();
};


#endif /* DECORATOR_H */