#ifndef CVIDA_H
#define CVIDA_H


#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <ComponentArch/Components/CTransform.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>

#include <GameAI/NavmeshStructs.hpp>
#include <Util.hpp>
#include <stack>


#include <ComponentArch/ObjectManager.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <Singleton.hpp>


class CVida : public IComponent {
    friend class Factory;
    public:
        CVida(int _vida);
        virtual ~CVida();
        float getVida();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void FixedUpdate();
        void Muerte();

        bool quitarvida(const float&);
        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();


    private:
        CVida(const CVida &orig) = delete;
        ObjectManager   *Manager;
        //ScreenConsole   *hud;
        CTriggerSystem  *triggerSystem;

        float vida;
        float vida_max;
        //CRigidBody* cRigidBody;
};

#endif
