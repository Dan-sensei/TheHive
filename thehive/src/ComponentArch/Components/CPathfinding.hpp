#ifndef CPAHTINDING_H
#define CPAHTINDING_H


#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <GameAI/NavmeshStructs.hpp>
#include <Util.hpp>
#include <stack>

#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include "CTransform.hpp"
#include <Singleton.hpp>

//#include "CRigidBody.hpp"


class CPathfinding : public IComponent {
    friend class Factory;
    public:
        virtual ~CPathfinding();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();
        gg::EMessageStatus MHandler_UPDATE  ();


    private:
        CPathfinding();
        CPathfinding(const CPathfinding &orig) = delete;

        GameEngine* Engine;
        CTransform* cTransform;
        std::stack<Waypoint> Waypoints;
        uint16_t currentWaypointID;

        //CRigidBody* cRigidBody;
};

#endif
