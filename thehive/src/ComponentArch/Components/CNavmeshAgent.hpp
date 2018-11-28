#ifndef CNAVMESHAGENT_H
#define CNAVMESHAGENT_H


#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <GameAI/NavmeshStructs.hpp>
#include <Util.hpp>
#include <stack>

#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include "CTransform.hpp"
#include <Singleton.hpp>

#include "CRigidBody.hpp"


class CNavmeshAgent : public IComponent {
    friend class Factory;
    public:
        virtual ~CNavmeshAgent();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();
        gg::EMessageStatus MHandler_UPDATE  ();

        void SetDestination(const gg::Vector3f &Target);
        bool HasDestination();


    private:
        CNavmeshAgent();
        CNavmeshAgent(const CNavmeshAgent &orig) = delete;

        GameEngine* Engine;
        CTransform* cTransform;
        std::stack<Waypoint> Waypoints;
        uint16_t currentWaypointID;

        CRigidBody* cRigidBody;

        bool        currentlyMovingTowardsTarget;
};

#endif
