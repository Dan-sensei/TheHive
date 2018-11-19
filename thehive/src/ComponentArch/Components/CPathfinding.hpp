#ifndef CPAHTINDING_H
#define CPAHTINDING_H


#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <Util.hpp>
#include <stack>


class GameEngine;
class CTransform;

class CPathfinding : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CPathfinding();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void initializeComponentData(const void* data);

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();
        gg::EMessageStatus MHandler_UPDATE  ();


    private:
        CPathfinding();
        CPathfinding(const CPathfinding &orig) = delete;

        std::stack<gg::Vector3f> Waypoints;


        CTransform* cTransform;
        GameEngine* engine;
};

#endif
