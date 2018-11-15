#ifndef _CGRANADE_H
#define _CGRANADE_H
#include <chrono>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>

class CTransform;
class ObjectManager;
class GameEngine;
class CTriggerSystem;

class CGranade: public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CGranade();

        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void initializeComponentData(const void* data);


        gg::EMessageStatus MHandler_SETPTRS();
        gg::EMessageStatus MHandler_UPDATE();

    private:
        CGranade();
        CGranade(const CGranade &orig);
        std::chrono::high_resolution_clock::time_point  begin;
        double elapsedtime;
        CTransform* cTransform;
        GameEngine* engine;
        ObjectManager* Manager;
        CTriggerSystem* EventSystem;


};

#endif
