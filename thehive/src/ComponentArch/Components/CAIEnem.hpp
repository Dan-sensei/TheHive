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
#include <Bullet/ggDynWorld.hpp>

#include <ComponentArch/Components/CClock.hpp>

#include <SurrealEngine/SurrealEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <GameAI/Treecontroller.hpp>

#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>

class Treecontroller;
class ObjectManager;

class CAgent;
class CTransform;
class CNavmeshAgent;
class ggDynWorld;

class CAIEnem : public IComponent {
    public:
        CAIEnem(gg::EEnemyType _type, float _agresividad, glm::vec3 _playerPos, bool _playerSeen);
        CAIEnem(const CAIEnem &orig) = delete;
        virtual ~CAIEnem();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();
        virtual void FixedUpdate();
        virtual void Update();

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        void MHandler_SENYUELO(TriggerRecordStruct* cdata);
        void MHandler_SENYUELO_END();
        void MHandler_NEAR(TriggerRecordStruct* cdata){}
        void MHandler_ATURD();

        void resetMyOwnTree();

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

        bool getPlayerSeeing();

        void upgradeMaxAliensAttackingAtOnce();
        int getMaxAliensAttackingAtOnce();

        void upgradeRage();
        float getRage();

        void resetHabilityUpdateCounter();
        int getHabilityUpdateCounter();

        void explosiveWave();

        int getEnemyType();
        float getVelocity();

        void playMovement();
        void playAttack();
        void playAttack2();
        // /////////////////////////////////////////////// //
        // JAVI CAMBIA LO DE LAS VARIABLES PUBLICAS !      //
        // /////////////////////////////////////////////// //

        static CTransform* PlayerTransform;     //  Punteros a otras componentes
        static CRigidBody* PlayerBody;     //  Punteros a otras componentes
        Treecontroller* arbol;

        glm::vec3 playerPos;
        glm::vec3 senpos;
        glm::vec3 destino;
        float enfado;
        float agresividad;
        float Vrange;
        float Arange;
        float gradovision;

        Blackboard* data;

        int signo;
        int ID;
        int ultrasonido_cont;
        int rondacion_cont;


        bool playerSeen;
        bool playerOnRange;
        bool playerSeeing;
        bool ultrasonido;
        bool senyuelo;
        bool            CanIReset;

    private:
        SurrealEngine      *Engine;
        ObjectManager   *Manager;
        CTriggerSystem  *EventSystem;
        CTransform      *cTransform;
        CAgent          *cAgent;
        ggDynWorld      *world;

        // CNavmeshAgent   *nvAgent;

        gg::EEnemyType type;
        int             numberOfUpdatesSinceLastHability;
        int             maxAliensAttacking;
        float             velocity;

        static bool     debugvis;
        bool            imAttacking;
        bool            isPlayerAttacking;
        bool            closerAllyIsDead;

        SoundSystem* SS;

        SoundEvent* s_caminar;
        SoundEvent* s_atacar;
        SoundEvent* s_atacar2;
        //bool            CanIReset;

        void enableVisualDebug();
};

#endif
