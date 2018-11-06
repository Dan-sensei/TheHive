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
  inverso(behavior* _m_pChild);
  inverso();
  ~inverso();

  virtual void onTerminate(Status state);

 virtual Status update();
 //virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
 //virtual void onTerminate(Status);

};



#endif /* DECORATOR_H */
