#ifndef _CGUN_H
#define _CGUN_H

#include <vector>
#include <chrono>


#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <EventSystem/CTriggerSystem.hpp>
#include "CTransform.hpp"
//#include <Factory.hpp>
#include <Util.hpp>
#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>
#include <FMOD/SonidoEscopeta.hpp>

class CGun : public IComponent {
    public:
        CGun(float, float, int, float, float, int, std::string, std::string, std::string, std::string);                //  No queremos que alguien lo construya fuera (Limón)
        CGun(const CGun &orig) = delete;
        virtual ~CGun();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();
        virtual void FixedUpdate();

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes

        // Funciones propias de CGun
        void shoot(glm::vec3);
        void reload();
        bool isReloading();
        int getBullets();
        int getTotalBullets();
        int getType();
        void desenfundado();


    private:
        ObjectManager* Manager;

        //  Punteros a otras componentes
        CTransform* cTransform;

        //  Variables de esta componente
        int     ktotal_bullets;
        float   damage;
        float   cadence;
        int     total_bullets;
        float   reloadDT;
        float   range;

        // SoundSystem* SS;
        //
        // SoundEvent* s_disparo;
        // SoundEvent* s_recarga;
        // SoundEvent* s_desenfundado;
        // SoundEvent* s_vacio;

        int     WEAPON_TYPE;
        bool    canShoot;
        bool    reloading;
        std::chrono::high_resolution_clock::time_point dtCadence;
        std::chrono::high_resolution_clock::time_point dtReload;
};

#endif
