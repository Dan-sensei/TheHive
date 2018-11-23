#ifndef _CAIENEM_H
#define _CAIENEM_H

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
#include <cstdint>
#include <list>
#include <vector>
//#include <irrlicht>

#include <Util.hpp>
#include <EventSystem/EnumTriggerType.hpp>
#include <EventSystem/CTriggerSystem.hpp>

#include <ComponentArch/Message.hpp>
#include <ComponentArch/Enum.hpp>
#include <BT/BehaviorTree.hpp>


#include "CAgent.hpp"
                                                //            punteros a otras componentes


class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CTransform;           //  Forward declaration de otras componentes que incluyas

class CAIEnem : public IComponent {
    friend class ObjectManager;                 // Con esto le decimos que sólo ObjectManager puede crear esta componente
    public:


        gg::EEnemyType type;
        float agresividad;
        gg::Vector3f playerPos;
        bool playerSeen;

        //des/activar eventos sonoros


        bool playerOnRange;
        float enfado;
        BehaviorTree* BT;


        void enemyseen(TriggerRecordStruct* cdata);

        //uint16_t getEntityID();upda

        virtual ~CAIEnem();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void initializeComponentData(const void* data);         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

    private:
        CAIEnem();                //  No queremos que alguien lo construya fuera (Limón)
        CAIEnem(const CAIEnem &orig) = delete;
        //CAIEnem(unsigned long _dwTriggerFlags,gg::Vector3f _vPos);

        using Behaviors = std::vector<Behavior*>;
        Behaviors m_Children;


        GameEngine* engine;

        CTransform* cTransform;     //  Punteros a otras componentes
        CAgent* cAgent;     //  Punteros a otras componentes


};

#endif
