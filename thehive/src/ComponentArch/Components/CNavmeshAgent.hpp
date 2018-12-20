#ifndef CNAVMESHAGENT_H
#define CNAVMESHAGENT_H


#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <GameAI/NavmeshStructs.hpp>
#include <Util.hpp>
#include <stack>

#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <Singleton.hpp>

#include "CTransform.hpp"

#include <Bullet/ggDynWorld.hpp>
#include "CRigidBody.hpp"

class CRigidBody;

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
        gg::EMessageStatus MHandler_SETNEWPOSITION (const Message &m);

        void SetDestination(const gg::Vector3f &Target);
        bool HasDestination();

        std::stack<Waypoint> Waypoints;

    private:
        CNavmeshAgent();
        CNavmeshAgent(const CNavmeshAgent &orig) = delete;

        GameEngine* Engine;
        ggDynWorld* world;

        CTransform* cTransform;
        uint16_t currentWaypointID;

        CRigidBody* cRigidBody;

        bool        currentlyMovingTowardsTarget;
        float SightDistance;

        gg::Vector3f DebugMoveVector;
};

#endif
