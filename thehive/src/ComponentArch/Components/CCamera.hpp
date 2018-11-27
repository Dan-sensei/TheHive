#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <cstdint>
#include <cmath>
#include <GameEngine/GameEngine.hpp>
#include <GameEngine/Camera.hpp>
#include "CTransform.hpp"
#include <Singleton.hpp>


class ObjectManager;

class CCamera : public IComponent {
friend class Factory;
public:
    CCamera(bool);
    CCamera(const CCamera &orig) = delete;
    virtual ~CCamera ();

    // Functions of IComponent
    static void initComponent();
    virtual gg::EMessageStatus processMessage(const Message &m);
    virtual void Init();

    //  Handlers
    gg::EMessageStatus MHandler_SETPTRS();

    void updateCameraTarget(gg::Vector3f, bool);
    gg::Vector3f getCameraPosition();
    gg::Vector3f getCameraRotation();
    gg::Vector3f getCameraTarget();

    gg::Vector3f getlastHeroPosition();
    gg::Vector3f getCameraPositionBeforeLockRotation();
    void setCameraPositionBeforeLockRotation(gg::Vector3f);

private:

    gg::Vector3f lastHeroPosition;
    gg::Vector3f cameraPositionBeforeLockRotation;

    GameEngine *Engine;
    ObjectManager *Manager;
    Camera* cam;
    CTransform *mod;

    bool daniNoSabeProgramar;
};


#endif
