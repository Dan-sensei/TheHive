#ifndef ANDAR_RAND_HPP
#define ANDAR_RAND_HPP

#include "Behavior.hpp"
#include <iostream>

class Andar_rand : public Behavior {
    public:
      Andar_rand();
      ~Andar_rand();

       // behavior() : m_eStatus(BH_INVALID)  {}    // Constructor. No se declara en la interfaz, sino en sus hijos, SUPONGO
       virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
       virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
       virtual void onTerminate(Status);        // Si ya no se realiza el update, onTerminate() es llamado inmediatamente despues

       void setFailed();
       bool getFailed();
   private:
       bool failed;
};
#endif
