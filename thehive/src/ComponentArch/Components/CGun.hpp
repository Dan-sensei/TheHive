#ifndef _CGUN_H
#define _CGUN_H

#include <vector>
#include <Util.hpp>

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include "CTransform.hpp"

class CGun : public IComponent {
    public:
        CGun(float _dmg, float _cadence, int _total_bullets);                //  No queremos que alguien lo construya fuera (Limón)
        CGun(const CGun &orig) = delete;
        virtual ~CGun();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

        // Funciones propias de CGun
        void shoot(gg::Vector3f);
        int getBullets();

    private:

        GameEngine* Engine;
        ObjectManager* Manager;

        //  Punteros a otras componentes
        CTransform* cTransform;

        //  Variables de esta componente
        int total_bullets;
        float damage;
        float cadence;
        std::vector<uint8_t> bullets;
};

#endif
