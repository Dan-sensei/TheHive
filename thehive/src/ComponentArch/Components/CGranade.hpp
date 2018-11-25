#ifndef _CGRANADE_H
#define _CGRANADE_H
#include <chrono>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>

#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <EventSystem/EnumTriggerType.hpp>
#include "EventSystem/CTriggerSystem.hpp"
#include "CTransform.hpp"

#include <Singleton.hpp>



class CGranade: public IComponent {
    public:
        CGranade(float _damage,float _radius,float _tipo);
        CGranade(const CGranade &orig) = delete;
        virtual ~CGranade();

        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();


        gg::EMessageStatus MHandler_SETPTRS();
        gg::EMessageStatus MHandler_UPDATE();

    private:
        std::chrono::high_resolution_clock::time_point begin;
        double elapsedtime;
        float damage;
        float radius;
        float tipo;
        CTransform* cTransform;
        GameEngine* engine;
        ObjectManager* Manager;
        CTriggerSystem* EventSystem;


};

#endif
