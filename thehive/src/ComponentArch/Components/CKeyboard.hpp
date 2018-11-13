#ifndef _CKEYBOARD_H
#define _CKEYBOARD_H

#include <cmath>
#include <map>

#include <GameEngine/GameEngine.hpp>
#include <GameEngine/KEYCODES.hpp>

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Message.hpp>


class CCamera;
class CTransform;
class CRigidBody;
class GameEngine;
class ObjectManager;

class CKeyboard : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CKeyboard();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void initializeComponentData(const void* data);

        // Handlers
        gg::EMessageStatus MHandler_SETPTRS ();
        gg::EMessageStatus MHandler_UPDATE  ();


    private:
        CKeyboard();
        CKeyboard(const CKeyboard &orig) = delete;


        CTransform* cTransform;
        CRigidBody* cRigidBody;
        CCamera *camera;
        GameEngine* engine;
        gg::Vector2f DASH_SPEED;
        gg::Vector2f RUNNING_SPEED;
};

#endif
