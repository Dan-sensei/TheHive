#ifndef _CCLOCK_H
#define _CCLOCK_H

#include <chrono>

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
                                                //            punteros a otras componentes
class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CCamera;           //  Forward declaration de otras componentes que incluyas
class CTransform;

class CClock : public IComponent {
    public:
        CClock();                               //  <<-- AHORA PUEDE RECIBIR PARÁMETROS!
        CClock(const CClock &orig) = delete;
        virtual ~CClock();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();                                            // [OPCIONAL]

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

        // Funciones propias
        bool startChrono(float);
        bool setEndTime(float);
        float getActualTime();
        bool hasEnded();

    private:
        GameEngine* engine;

        bool initialized;
        bool limitReached;
        float msEnd;
        std::chrono::high_resolution_clock::time_point begin;

};

#endif
