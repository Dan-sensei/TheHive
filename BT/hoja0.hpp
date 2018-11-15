#ifndef hoja0_HPP
#define hoja0_HPP

#include "Behavior.hpp"
#include <iostream>
  class hoja0 : public Behavior {

public:
  hoja0();
  ~hoja0();
  int contador;
   // behavior() : m_eStatus(BH_INVALID)  {}    // Constructor. No se declara en la interfaz, sino en sus hijos, SUPONGO
   virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
   virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
   virtual void onTerminate(Status);        // Si ya no se realiza el update, onTerminate() es llamado inmediatamente despues



};

#endif /* BEHAVIOR_HPP */
