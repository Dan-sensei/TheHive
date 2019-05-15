#ifndef _CHABILITYCONTROLLER_H
#define _CHABILITYCONTROLLER_H

#include <cmath>
#include <map>

#include <Bullet/ggDynWorld.hpp>

#include <Omicron/KEYCODES.hpp>
#include <Omicron/2D/HUD.hpp>

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Message.hpp>
#include <GameAI/Hability.hpp>
#include <GameAI/Hability1.hpp>
#include <GameAI/Hability2.hpp>
#include <GameAI/Hability3.hpp>


#include <Singleton.hpp>

//class Hability;
// class CCamera;
// class CTransform;
// class CRigidBody;
// class CGun;

// class GameEngine;
// class ObjectManager;
// class ggDynWorld;

class CHabilityController : public IComponent {

    public:
        CHabilityController();
        virtual ~CHabilityController();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void FixedUpdate();


        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();

        void ToggleSkill(int HabilityID);


    private:
        HUD* hud;
        CHabilityController(const CHabilityController &orig) = delete;

        std::vector<void (CHabilityController::*)(const float&)> vHabs;
        void updateHudCooldown_TR(const float &cd);
        void updateHudCooldown_TL(const float &cd);
        void updateHudCooldown_BM(const float &cd);

        Hability* Habilities[3];
        //Hability hab2;
        //Hability hab3;



};

#endif
