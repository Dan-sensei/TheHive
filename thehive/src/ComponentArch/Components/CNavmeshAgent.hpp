#ifndef CNAVMESHAGENT_H
#define CNAVMESHAGENT_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <GameAI/NavmeshStructs.hpp>
#include <Util.hpp>
#include <stack>

#include <SurrealEngine/TMotorTAG.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <Singleton.hpp>

#include "CTransform.hpp"



#include <GameEngine/Clock.hpp>
class CRigidBody;
class ggDynWorld;

class CNavmeshAgent : public IComponent {
    friend class Factory;
    public:
        virtual ~CNavmeshAgent();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void Update();
        virtual void FixedUpdate();

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();

        void SetDestination(const gg::Vector3f &Target);
        bool HasDestination();
        void ResetDestination();

        std::stack<Waypoint> Waypoints;

    private:
        CNavmeshAgent();
        CNavmeshAgent(const CNavmeshAgent &orig) = delete;

        void CheckShortcut();
        void ApplyCouterForce(const gg::Vector3f &DirVector);

        gg::Clock Timer;
        gg::Vector3f RS, LS;
        gg::Vector3f moveVector;

        TMotorTAG* Engine;
        ggDynWorld* world;

        CTransform* cTransform;

        CRigidBody* cRigidBody;

        float SightDistance;
        uint16_t currentWaypointID;
        bool        currentlyMovingTowardsTarget;
};

#endif
