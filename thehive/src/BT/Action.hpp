#ifndef ACTION_HPP
#define ACTION_HPP

#include "Behavior.hpp"
#include "Hojas.hpp"

#include <iostream>
#include <string>
#include <random>

#include <Util.hpp>

#include "EventSystem/Blackboard.hpp"
#include "EventSystem/BVector3f.hpp"
#include "EventSystem/BInt.hpp"
#include "EventSystem/BBool.hpp"

#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>
#include <ComponentArch/Components/CTransform.hpp>
#include <ComponentArch/Components/CRigidBody.hpp>
#include <ComponentArch/Components/CVida.hpp>

class Action : public Behavior {
    public:
        Action(Hojas task,Blackboard* _data,CAIEnem* ai);
        virtual ~Action();
        Action(const Action &orig);
        // behavior() : m_eStatus(BH_INVALID)  {}    // Constructor. No se declara en la interfaz, sino en sus hijos, SUPONGO
        virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
        virtual Status update() ;              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
        virtual void onTerminate(Status);        // Si ya no se realiza el update, onTerminate() es llamado inmediatamente despues
        virtual void abort();

        void setActive(std::string a, bool acierto);
        void andar_random();
        void comer_animal();
        void rango_visual();
        void move_to();
        void move_too(int min);
        void girar_enemigo();

        void distancia10();
        void distancia20();
        void distancia(float,gg::Vector3f);

        void over_2_meters();
        void over_X_meters(int);

        void FIVE_SinceLastHability();

        void onrange();
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
        void rond(bool = true);
        void hit();
        void playerNotAttacking();
        void isThereSomeAlienDead();
        void moreRage();
        void checkAliensAttacking();
        void alienInPause();
        void move_player_utilx();
        void imatack();
        void modifyImAttacking(bool);
        void setOffsetAliensAttacking(int);
        void doExplosiveWave();
        void doSpit();


        CAIEnem* yo;
        static int aliensAttacking;

   private:
        CRigidBody       *cRigidBody;
        ObjectManager    *manager;
        CTransform       *cTransform;

        Blackboard* data;

        using pFunc = void(Action::*)();
        pFunc VectorAcciones[NUM_ACCIONES];

        Status s;
        Hojas tarea;

        // Variables del BT
        int cont_hit;
        int cont_pause;
};

#endif
