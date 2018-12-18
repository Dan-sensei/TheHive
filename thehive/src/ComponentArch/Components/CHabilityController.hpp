#ifndef _CHABILITYCONTROLLER_H
#define _CHABILITYCONTROLLER_H

#include <cmath>
#include <map>

#include <GameEngine/GameEngine.hpp>
#include <Bullet/ggDynWorld.hpp>
#include <GameEngine/KEYCODES.hpp>

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Message.hpp>
#include <GameAI/Hability.hpp>
#include <GameAI/Hability1.hpp>
#include <GameAI/Hability2.hpp>
#include <GameAI/Hability3.hpp>

#include <Singleton.hpp>

//class Hability;
class CCamera;
class CTransform;
class CRigidBody;
class CGun;

class GameEngine;
class ObjectManager;
class ggDynWorld;

class CHabilityController : public IComponent {

    public:
        CHabilityController();
        virtual ~CHabilityController();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void Update();


        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();

        void pulsado(int hab);

    private:
        CHabilityController(const CHabilityController &orig) = delete;


        Hability hab[3];
        //Hability hab2;
        //Hability hab3;



};

#endif
