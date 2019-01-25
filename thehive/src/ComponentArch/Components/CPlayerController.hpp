#ifndef _CPLAYERCONTROLLER_H
#define _CPLAYERCONTROLLER_H

#include <cmath>
#include <map>
#include <string>

#include <Util.hpp>

#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <Bullet/ggDynWorld.hpp>
#include "Factory.hpp"

#include <GameEngine/KEYCODES.hpp>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <GameEngine/Clock.hpp>

#define NUMBER_OF_ITEMS     3

class CCamera;
class CTransform;
class CRigidBody;
class CGun;
class CHabilityController;

class GameEngine;
class ObjectManager;
class ggDynWorld;
class Factory;

class CPlayerController : public IComponent {
    friend class Factory;
    public:
        //static int cont_enemigos;
        virtual ~CPlayerController();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void FixedUpdate();
        virtual void Update();

        int setSecondWeapon(CGun*);
        bool heroHasSecondWeapon();
        bool canPickWeapon();

        bool hasItem(const uint16_t&);
        bool pickItem(const uint16_t&);
        bool useItem(const uint16_t&);

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();

        void SprintBuf();
        void SprintDebuf();
        int maxsoldier;
        int maxrusher;
        int maxtank;

        int currentsoldier;
        int currentrusher;
        int currenttank;
    private:

        CPlayerController();
        CPlayerController(const CPlayerController &orig) = delete;

        gg::Clock clocker;
        gg::Vector3f Target;

        ObjectManager* Manager;
        Factory* factory;
        GameEngine* Engine;
        ggDynWorld* world;
        CTransform* cTransform;
        CRigidBody* cRigidBody;
        CCamera* camera;
        CHabilityController* hab;
        bool GranadeCreate;

        bool pulsacion_granada;
        bool pulsacion_soldier;
        bool pulsacion_tank;
        bool pulsacion_rusher;
        //bool pulsacion_enemigos;
        bool pulsacion_espacio;
        bool pulsacion_q;
        bool pulsacion_dash;
        bool pulsacion_f;

        bool debug1;
        bool debug2;
        float MULT_BASE;

        bool isPrincipal; // True -> PRINCIPAL | False -> SECUNDARIA
        CGun *secondWeapon;
        std::array<uint16_t,NUMBER_OF_ITEMS> items;

        gg::Vector3f cV,ppV;
        // std::map<int, void (CPlayerController::*)(gg::Vector3f&,bool&)> mapPlayerActions;
        void W_IsPressed(gg::Vector3f&,bool&);
        void A_IsPressed(gg::Vector3f&,bool&);
        void S_IsPressed(gg::Vector3f&,bool&);
        void D_IsPressed(gg::Vector3f&,bool&);
        void ApplyDash(gg::Vector3f&,float&);
        void showDebug();
        void changeWeaponIfPossible(CGun*);

        int actualGrenadeState; // 1,2,3
        std::map<int, void (CPlayerController::*)()> mapFuncGrenades;
        void playerThrowHolyBomb();
        void playerThrowMatrioska();
        void playerThrowDopple();
};

#endif
