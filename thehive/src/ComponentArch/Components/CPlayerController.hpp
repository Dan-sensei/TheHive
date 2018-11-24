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

#include <Singleton.hpp>


class CCamera;
class CTransform;
class CRigidBody;
class CGun;

class GameEngine;
class ObjectManager;
class ggDynWorld;

class CPlayerController : public IComponent {
    friend class Factory;
    public:
        virtual ~CPlayerController();

        // Functions of IComponent
        bool pulsacion_granada;
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();
        gg::EMessageStatus MHandler_UPDATE  ();


    private:
        CPlayerController();
        CPlayerController(const CPlayerController &orig) = delete;

        ObjectManager* Manager;
        GameEngine* Engine;
        ggDynWorld* world;

        CTransform* cTransform;
        CRigidBody* cRigidBody;
        CCamera *camera;
        bool GranadeCreate;
};

#endif
