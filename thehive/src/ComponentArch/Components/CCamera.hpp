#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <cstdint>
#include <cmath>
#include <GameEngine/GameEngine.hpp>
#include <GameEngine/Camera.hpp>
#include <Singleton.hpp>
#include <Bullet/ggDynWorld.hpp>

#include "CTransform.hpp"

class ObjectManager;
class CRigidBody;

class CCamera : public IComponent {
friend class Factory;
public:
    CCamera(bool);
    CCamera(const CCamera &orig) = delete;
    virtual ~CCamera ();

    // Functions of IComponent
    virtual gg::EMessageStatus processMessage(const Message &m);
    virtual void Init();

    //  Handlers
    gg::EMessageStatus MHandler_SETPTRS();

    void updateCameraTarget(gg::Vector3f, bool);
    gg::Vector3f getCameraPosition();
    gg::Vector3f getCameraRotation();
    gg::Vector3f getCameraTarget();
    gg::Vector3f getOffsetPositionVector();

    void moveCameraPosition(gg::Vector3f);

    gg::Vector3f getlastHeroPosition();
    gg::Vector3f getCameraPositionBeforeLockRotation();
    void setCameraPositionBeforeLockRotation(gg::Vector3f);

    float getSenA(){return senA;}
    float getCosA(){return cosA;}

private:
    gg::Vector3f lastHeroPosition;
    gg::Vector3f cameraPositionBeforeLockRotation;

    GameEngine *Engine;
    ObjectManager *Manager;
    Camera* cam;
    CTransform *mod;

    bool daniNoSabeProgramar;
    gg::Vector3f offsetPositionVector;

    float senA,cosA;

    uint16_t entCollisions;
    CTransform *collTF;

    bool collision;
    gg::Vector3f pos_on_collision;
    gg::Vector3f last_cam_position;
};


#endif
