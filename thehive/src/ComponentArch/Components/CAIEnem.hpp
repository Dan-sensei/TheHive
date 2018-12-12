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
class Treecontroller;
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
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();
        virtual void Update();

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        void MHandler_SENYUELO(TriggerRecordStruct* cdata);
        void MHandler_SENYUELO_END();

        void MHandler_ATURD();

        void MHandler_NEAR(TriggerRecordStruct* cdata);


        //void MHandler_ATURD_END();


        void enemyseen();
        void enemyrange();


        //new Blackboard datos*;
        //dato add("type",TIPO_EENEMYTYPE,4)
        //dato add("type",TIPO_EENEMYTYPE,4)
        gg::EEnemyType type;
        float agresividad;
        float Vrange;
        float Arange;

        //des/activar eventos sonoros
        Blackboard* data;

        float enfado;
        //BehaviorTree* BT;
        Treecontroller* arbol;



        //uint16_t getEntityID();upda


        static CTransform* PlayerTransform;     //  Punteros a otras componentes

        gg::Vector3f playerPos;
        bool playerSeen;
        bool playerOnRange;

        bool playerSeeing;
        bool ultrasonido;
        bool senyuelo;
        gg::Vector3f senpos;
        gg::Vector3f destino;
        int id;
        int id2;
        int ultrasonido_cont;
        int rondacion_cont;
        float gradovision;
    private:
        static bool debugvis;
        //bool playerSeen;
        //bool playerOnRange;
        //gg::Vector3f playerPos;


        //CAIEnem(unsigned long _dwTriggerFlags,gg::Vector3f _vPos);

        //using Behaviors = std::vector<Behavior*>;
        //Behaviors m_Children;


        GameEngine* Engine;

        CTransform* cTransform;     //  Punteros a otras componentes
        CAgent* cAgent;     //  Punteros a otras componentes

        void enableVisualDebug();

};

#endif
