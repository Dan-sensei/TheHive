#ifndef _CGRANADE_H
#define _CGRANADE_H
#include <chrono>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>

#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>

#include <EventSystem/EnumTriggerType.hpp>
#include "EventSystem/CTriggerSystem.hpp"
#include <EventSystem/TData.hpp>

#include "CTransform.hpp"
#include "Factory.hpp"


class CGranade: public IComponent {
    public:
        CGranade();
        CGranade(float _radius);
        CGranade(const CGranade &orig) = delete;
        virtual ~CGranade();

        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void explosion();



        gg::EMessageStatus MHandler_SETPTRS();
        gg::EMessageStatus MHandler_UPDATE();

    protected:
        std::chrono::high_resolution_clock::time_point begin;
        double elapsedtime;
        float radius;
        CTransform* cTransform;
        GameEngine* engine;
        ObjectManager* Manager;
        CTriggerSystem* EventSystem;


};

#endif
