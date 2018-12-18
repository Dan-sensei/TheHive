#ifndef _CAIENEM_H
#define _CAIENEM_H

#include <cstdint>
#include <list>
#include <vector>
#include <Util.hpp>
#include <Singleton.hpp>

#include <EventSystem/EnumTriggerType.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include "EventSystem/Blackboard.hpp"

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>
#include <ComponentArch/Enum.hpp>
#include <ComponentArch/Components/CClock.hpp>

#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <GameAI/Treecontroller.hpp>

class Treecontroller;
class CAgent;
class GameEngine;
class ObjectManager;

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

        void enemyseen();
        void enemyrange();

        void setPlayerIsAttacking(bool);
        bool getPlayerIsAttacking();

        void setCloserAllyIsDead(bool);
        bool getCloserAllyIsDead();

        void setImAttacking(bool);
        bool getImAttacking();

        void setSigno(int);
        int getSigno();

        void upgradeRage();
        float getRage();

        void resetHabilityUpdateCounter();
        int getHabilityUpdateCounter();

        void explosiveWave();

        int getEnemyType();
        // /////////////////////////////////////////////// //
        // JAVI CAMBIA LO DE LAS VARIABLES PUBLICAS !      //
        // /////////////////////////////////////////////// //

        static CTransform* PlayerTransform;     //  Punteros a otras componentes
        Treecontroller* arbol;

        gg::Vector3f playerPos;
        gg::Vector3f senpos;
        gg::Vector3f destino;
        float enfado;
        float agresividad;
        float Vrange;
        float Arange;
        float gradovision;

        Blackboard* data;

        int signo;
        int id;
        int id2;
        int ultrasonido_cont;
        int rondacion_cont;


        bool playerSeen;
        bool playerOnRange;
        bool playerSeeing;
        bool ultrasonido;
        bool senyuelo;

    private:
        GameEngine      *Engine;
        ObjectManager   *Manager;
        CTriggerSystem  *EventSystem;
        CTransform      *cTransform;
        CAgent          *cAgent;

        gg::EEnemyType type;
        int             numberOfUpdatesSinceLastHability;

        static bool     debugvis;
        bool            imAttacking;
        bool            isPlayerAttacking;
        bool            closerAllyIsDead;

        void enableVisualDebug();
};

#endif
