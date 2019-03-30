#ifndef _CPLAYERCONTROLLER_H
#define _CPLAYERCONTROLLER_H

#include <cmath>
#include <map>
#include <string>

#include <Util.hpp>

#include <Singleton.hpp>
#include <Omicron/Omicron.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <Bullet/ggDynWorld.hpp>
#include "Factory.hpp"

#include <GameEngine/KEYCODES.hpp>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <Omicron/Clock.hpp>
#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>
#include <FMOD/SonidoSuperficie.hpp>

#define NUMBER_OF_ITEMS     3

class CCamera;
class CTransform;
class CRigidBody;
class CDynamicModel;
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
        void invocasionhorda();
        void invocasionwander();


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
        glm::vec3 Target;

        ObjectManager* Manager;
        Factory* factory;
        Omicron* Engine;
        ggDynWorld* world;
        CTransform* cTransform;
        CRigidBody* cRigidBody;
        CCamera* camera;
        CDynamicModel* cDynamicModel;
        CHabilityController* hab;
        bool GranadeCreate;

        SoundSystem* SS;
        SoundEvent* s_dash;

        bool pulsacion_granada;
        bool pulsacion_soldier;
        bool pulsacion_tank;
        bool pulsacion_rusher;
        //bool pulsacion_enemigos;
        bool pulsacion_espacio;
        bool pulsacion_q;
        bool pulsacion_dash;
        bool pulsacion_f;

        bool FreeCamera;
        bool ToggleFreeCameraKey;
        bool PlayerMovement;

        bool debug1;
        bool debug2;
        float MULT_BASE;


        //SoundEvent* s_pasos;

        bool isPrincipal; // True -> PRINCIPAL | False -> SECUNDARIA
        CGun *secondWeapon;
        std::array<uint16_t,NUMBER_OF_ITEMS> items;

        glm::vec3 cV,ppV;
        // std::map<int, void (CPlayerController::*)(glm::vec3&,bool&)> mapPlayerActions;
        void W_IsPressed(glm::vec3&,bool&);
        void A_IsPressed(glm::vec3&,bool&);
        void S_IsPressed(glm::vec3&,bool&);
        void D_IsPressed(glm::vec3&,bool&);
        void ApplyDash(glm::vec3&,float&);
        void showDebug();
        void changeWeaponIfPossible(CGun*);

        int actualGrenadeState; // 1,2,3
        std::map<int, void (CPlayerController::*)()> mapFuncGrenades;
        void playerThrowHolyBomb();
        void playerThrowMatrioska();
        void playerThrowDopple();
};

#endif
