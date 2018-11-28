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
//#include <BT/BehaviorTree.hpp>
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine

#include <Singleton.hpp>
#include "EventSystem/Blackboard.hpp"
#include <GameAI/Treecontroller.hpp>


                                    //            punteros a otras componentes

class CAgent;
class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CTransform;           //  Forward declaration de otras componentes que incluyas

class CAIEnem : public IComponent {
    public:
        CAIEnem(gg::EEnemyType _type, float _agresividad, gg::Vector3f _playerPos, bool _playerSeen);
        CAIEnem(const CAIEnem &orig) = delete;
        virtual ~CAIEnem();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

        void enemyseen();
        void enemyrange();


        //new Blackboard datos*;
        //dato add("type",TIPO_EENEMYTYPE,4)
        //dato add("type",TIPO_EENEMYTYPE,4)
        gg::EEnemyType type;
        float agresividad;
        float Vrange;
        float Arange;
        gg::Vector3f playerPos;
        bool playerSeen;

        //des/activar eventos sonoros
        Blackboard* data;

        bool playerOnRange;
        float enfado;
        //BehaviorTree* BT;
        Treecontroller* arbol;



        //uint16_t getEntityID();upda


        static CTransform* PlayerTransform;     //  Punteros a otras componentes

    private:
        //CAIEnem(unsigned long _dwTriggerFlags,gg::Vector3f _vPos);

        //using Behaviors = std::vector<Behavior*>;
        //Behaviors m_Children;


        GameEngine* Engine;

        CTransform* cTransform;     //  Punteros a otras componentes
        CAgent* cAgent;     //  Punteros a otras componentes


};

#endif
