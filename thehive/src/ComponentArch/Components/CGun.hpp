#ifndef _CGUN_H
#define _CGUN_H

#include <vector>
#include <Util.hpp>

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
                                                //            punteros a otras componentes

class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

//  Forward declaration de otras componentes que incluyas
class CTransform;

class CGun : public IComponent {
    friend class ObjectManager;                 // Con esto le decimos que sólo ObjectManager puede crear esta componente
    public:
        virtual ~CGun();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void initializeComponentData(const void* data);         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

        // Funciones propias de CGun
        void shoot(gg::Vector3f);
        int getBullets();

    private:
        CGun();                //  No queremos que alguien lo construya fuera (Limón)
        CGun(const CGun &orig) = delete;

        GameEngine* engine;
        ObjectManager* manager;

        //  Punteros a otras componentes
        CTransform* cTransform;

        //  Variables de esta componente
        int total_bullets;
        float damage;
        float cadence;
        std::vector<uint8_t> bullets;
};

#endif
