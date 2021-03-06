#ifndef CNAVMESHAGENT_H
#define CNAVMESHAGENT_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <GameAI/NavmeshStructs.hpp>
#include <Util.hpp>
#include <stack>

#include <Omicron/Omicron.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <Singleton.hpp>

#include "CTransform.hpp"



#include <Omicron/Clock.hpp>
class CRigidBody;
class CAIEnem;
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

        void SetDestination(const glm::vec3 &Target);
        bool HasDestination();
        void ResetDestination();

        std::stack<Waypoint> Waypoints;

    private:
        CNavmeshAgent();
        CNavmeshAgent(const CNavmeshAgent &orig) = delete;

        void CheckShortcut();
        void ApplyCouterForce(const glm::vec3 &DirVector);

        gg::Clock Timer;
        glm::vec3 RS, LS;
        glm::vec3 moveVector;

        Omicron* Engine;
        ggDynWorld* world;

        CTransform* cTransform;

        // ----------------------------------
        CAIEnem*    AI;
        CRigidBody* ghostCollider;
        CRigidBody* collider;

        // ----------------------------------

        float SightDistance;
        uint16_t currentWaypointID;
        bool        currentlyMovingTowardsTarget;
        float vel;
};

#endif
