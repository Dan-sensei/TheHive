#ifndef RANGO_VISUAL_HPP
#define RANGO_VISUAL_HPP

#include "Behavior.hpp"
#include <iostream>

class Rango_visual : public Behavior {
    public:
      Rango_visual();
      ~Rango_visual();

       // behavior() : m_eStatus(BH_INVALID)  {}    // Constructor. No se declara en la interfaz, sino en sus hijos, SUPONGO
       virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
       virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
       virtual void onTerminate(Status);        // Si ya no se realiza el update, onTerminate() es llamado inmediatamente despues
};
#endif
