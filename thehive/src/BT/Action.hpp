#ifndef ACTION_HPP
#define ACTION_HPP

#include "Behavior.hpp"
#include "Hojas.hpp"
#include <iostream>

class Action : public Behavior {

    public:
      Action(Hojas task);
      virtual ~Action();

       // behavior() : m_eStatus(BH_INVALID)  {}    // Constructor. No se declara en la interfaz, sino en sus hijos, SUPONGO
       virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
       virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
       virtual void onTerminate(Status);        // Si ya no se realiza el update, onTerminate() es llamado inmediatamente despues

       void setActive(std::string a, bool acierto);
       void andar_random();
       void comer_animal();
       void rango_visual();
       void move_to();
       void girar_enemigo();

   private:

       using pFunc = void(Action::*)();
       pFunc VectorAcciones[NUM_ACCIONES];
       Status s;
       Hojas tarea;
};
#endif
