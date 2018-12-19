#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

#include "Status.hpp"

class Behavior{
    private:
        Status m_eStatus;
    public:
       // behavior() : m_eStatus(BH_INVALID)  {}    // Constructor. No se declara en la interfaz, sino en sus hijos, SUPONGO
       virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
       virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
       virtual void onTerminate(Status);        // Si ya no se realiza el update, onTerminate() es llamado inmediatamente despues
       virtual ~Behavior();

       bool isTerminate();
       virtual void abort();
       Status tick();
       Status getStatus();
};
#endif
