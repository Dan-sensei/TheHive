#ifndef _CGRANADE_H
#define _CGRANADE_H
#include <chrono>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>

#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>

#include <EventSystem/EnumTriggerType.hpp>
#include "EventSystem/CTriggerSystem.hpp"
#include <EventSystem/TData.hpp>

#include "CTransform.hpp"
#include "Factory.hpp"


class CGranade: public IComponent {
    public:
        CGranade();
        CGranade(float,int);
        CGranade(const CGranade &orig) = delete;
        virtual ~CGranade();

        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void FixedUpdate();

        virtual void explosion();

        gg::EMessageStatus MHandler_SETPTRS();

    protected:
        CTransform      *cTransform;
        CRigidBody      *cRigidBody;
        ObjectManager   *Manager;
        CTriggerSystem  *EventSystem;
        Factory         *factory;

        std::chrono::high_resolution_clock::time_point begin;
        double elapsedtime;
        float radius;
        int exTime;
        bool hasContact;


};

#endif
