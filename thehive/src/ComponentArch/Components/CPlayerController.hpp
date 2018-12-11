#ifndef _CPLAYERCONTROLLER_H
#define _CPLAYERCONTROLLER_H

#include <cmath>
#include <map>

#include <GameEngine/GameEngine.hpp>
#include <Bullet/ggDynWorld.hpp>
#include <GameEngine/KEYCODES.hpp>

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Message.hpp>
//#include <ComponentArch/Components/CHabilityController.hpp>
//#include <GameAI/Hability.hpp>

#include <Singleton.hpp>

#define NUMBER_OF_ITEMS     3

//class Hability;
class CCamera;
class CTransform;
class CRigidBody;
class CGun;
class CHabilityController;

class GameEngine;
class ObjectManager;
class ggDynWorld;

class CPlayerController : public IComponent {
    friend class Factory;
    public:
        virtual ~CPlayerController();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void FixedUpdate();

        int setSecondWeapon(CGun*);
        bool heroHasSecondWeapon();
        bool canPickWeapon();

        bool hasItem(const uint16_t&);
        bool pickItem(const uint16_t&);
        bool useItem(const uint16_t&);

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();

        void buf();
        void debuf();
    private:
        CPlayerController();
        CPlayerController(const CPlayerController &orig) = delete;

        ObjectManager* Manager;
        GameEngine* Engine;
        ggDynWorld* world;
        CTransform* cTransform;
        CRigidBody* cRigidBody;
        CCamera *camera;
        CHabilityController* hab;
        bool GranadeCreate;

        bool pulsacion_granada;
        bool pulsacion_espacio;
        bool pulsacion_q;
        bool pulsacion_dash;
        bool pulsacion_f;

        bool debug1;
        bool debug2;
        float           MULT_BASE;
        bool isPrincipal; // True -> PRINCIPAL | False -> SECUNDARIA
        CGun *secondWeapon;
        std::array<uint16_t,NUMBER_OF_ITEMS> items;
};

#endif
