#ifndef ACTION_HPP
#define ACTION_HPP

#include "Behavior.hpp"
#include "Hojas.hpp"
#include <iostream>
#include <string>
#include "EventSystem/Blackboard.hpp"

class Action : public Behavior {

    public:
      Action(Hojas task,Blackboard* _data);
      virtual ~Action();
      Action(const Action &orig);
       // behavior() : m_eStatus(BH_INVALID)  {}    // Constructor. No se declara en la interfaz, sino en sus hijos, SUPONGO
       virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
       virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
       virtual void onTerminate(Status);        // Si ya no se realiza el update, onTerminate() es llamado inmediatamente despues

       void setActive(std::string a, bool acierto);
       void andar_random();
       void comer_animal();
       void rango_visual();
       void move_to();
       void move_too();
       void girar_enemigo();
       void distancia10();
       void onrange();
       void distancia(float _dist);
       void seeing();
       void seen();
       void checkbool(std::string that);
       void move_around();
       void move_player();
       void move_last();




   private:
       Blackboard* data;
       using pFunc = void(Action::*)();
       pFunc VectorAcciones[NUM_ACCIONES];
       Status s;
       Hojas tarea;
};
#endif
