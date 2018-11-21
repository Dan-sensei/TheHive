#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <cstdint>
#include <cmath>


class GameEngine;
class ObjectManager;
class Camera;
class CTransform;

class CCamera : public IComponent {
friend class ObjectManager;
public:
    virtual ~CCamera ();

    // Functions of IComponent
    static void initComponent();
    virtual void initializeComponentData(const void *);
    virtual gg::EMessageStatus processMessage(const Message &m);

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
    CCamera();
    gg::Vector3f lastHeroPosition;
    gg::Vector3f cameraPositionBeforeLockRotation;

    GameEngine *engine;
    ObjectManager *manager;
    Camera* cam;

    CTransform *mod;
};


#endif
