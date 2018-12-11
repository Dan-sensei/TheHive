#ifndef CVIDA_H
#define CVIDA_H


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


class CVida : public IComponent {
    friend class Factory;
    public:
        CVida(int _vida);
        virtual ~CVida();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void Update();

        void quitarvida();
        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();


    private:
        CVida(const CVida &orig) = delete;
        ObjectManager* Manager;

        int vida;
        int vida_max;
        //CRigidBody* cRigidBody;
};

#endif
