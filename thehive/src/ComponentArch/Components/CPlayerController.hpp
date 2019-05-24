#ifndef _CPLAYERCONTROLLER_H
#define _CPLAYERCONTROLLER_H

#include <cmath>
#include <map>
#include <string>

#include <Util.hpp>
#include <Singleton.hpp>
#include "Factory.hpp"

#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <Bullet/ggDynWorld.hpp>

#include <Omicron/Omicron.hpp>
#include <Omicron/2D/HUD.hpp>
#include <Omicron/KEYCODES.hpp>
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

        void explosion(glm::vec3 vPos,float fuerzabomba);

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

        CRigidBody* ghostCollider;      //  Kinematico y ghost
        CRigidBody* collider;           //  "Gravedad 0" y colisionable
        glm::vec3 GH_PREV;
        bool isColliderGravitySet;

        gg::Clock clocker;
        glm::vec3 Target;

        HUD* hud;
        ObjectManager* Manager;
        Factory* factory;
        Omicron* Engine;
        ggDynWorld* world;
        CTransform* cTransform;
        CCamera* camera;
        CDynamicModel* cDynamicModel;
        CHabilityController* hab;
        CGun *secondWeapon;

        SoundSystem* SS;
        SoundEvent* s_dash;
        SoundEvent* s_pasos;
        SoundEvent* s_saltar;
        SoundEvent* s_saltarVoz;

        glm::vec3    force;
        glm::vec3 cV;
        float           MULT_FACTOR;
        bool FreeCamera;
        bool ToggleFreeCameraKey;
        bool PlayerMovement;
        bool pulsacion_f;

        bool pressed;

        bool debug1;
        bool debug2;
        float MULT_BASE;



        bool isPrincipal; // True -> PRINCIPAL | False -> SECUNDARIA
        std::array<uint16_t,NUMBER_OF_ITEMS> items;

        // std::map<int, void (CPlayerController::*)(glm::vec3&,bool&)> mapPlayerActions;
        void check_WASD(glm::vec3 &force, bool &flag_pressed);
        void showDebug();

        void autoStepping();

        struct Key2Func{
            gg::KEYCODE KEY;
            void (CPlayerController::*Target)();
        };

        std::array<Key2Func, 15> KEYMAP;

        void ToggleSkill1();
        void ToggleSkill2();
        void ToggleSkill3();
        void ReloadGun();
        void ThrowGranade();
        void ChangeWeapon();
        void Run();
        void DASH();
        void JUMP();
        void TogglePause();
        void MostrarTexto();
        // void QuitarTexto();
        void invocasionhorda();
        void invocasionwander();
        void ToggleFreeCamera();
        void EnemyInfo();
        void aim(const uint8_t &s);

        glm::quat GetQuaternionBetween_MaxAngle(glm::vec3 &V1, glm::vec3 &V2, glm::quat CurrentRotation, const float &MaxTurnAngle);
        glm::quat RotationBetween(glm::vec3 &V1, glm::vec3 &V2);

        int actualGrenadeState; // 1,2,3
        std::map<int, void (CPlayerController::*)()> mapFuncGrenades;
        void playerThrowHolyBomb();
        void playerThrowMatrioska();
        void playerThrowDopple();
};

#endif
