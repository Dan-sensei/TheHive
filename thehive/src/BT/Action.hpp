#ifndef ACTION_HPP
#define ACTION_HPP

#include "Behavior.hpp"
#include "Hojas.hpp"
#include <iostream>
#include <string>
#include "EventSystem/Blackboard.hpp"
#include "ComponentArch/Components/CAIEnem.hpp"


class Action : public Behavior {

    public:
      Action(Hojas task,Blackboard* _data,CAIEnem* ai);
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
       void distancia(float _dist,gg::Vector3f obj);
       void seeing();
       void ultrasonido();
       void senyuelo();
       void seen();
       void checkbool(bool that);
       void move_around();
       void move_senyuelo();
       void move_player();
       void move_last();
       void in_last();
       void ult_cont();
       void rond_seny();
       void rond_jugador();
       void rond();
       void player_vistocono();


CAIEnem* yo;


   private:
       Blackboard* data;
       using pFunc = void(Action::*)();
       pFunc VectorAcciones[NUM_ACCIONES];
       Status s;
       Hojas tarea;
};
#endif
