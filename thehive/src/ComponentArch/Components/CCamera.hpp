#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <cstdint>
#include <cmath>
#include <SurrealEngine/SurrealEngine.hpp>
#include <SurrealEngine/TNodo.hpp>
#include <Singleton.hpp>

#include "CTransform.hpp"
#include <ComponentArch/ObjectManager.hpp>

class ggDynWorld;
class CCamera : public IComponent {
friend class Factory;
public:
    CCamera(int8_t);
    CCamera(const CCamera &orig) = delete;
    virtual ~CCamera ();

    // Functions of IComponent
    virtual void Init();

    glm::vec3 getTargetPosition();
    void setTarget(CTransform* T);
    void CameraUpdate();

    void FollowTarget();
    void FreeCamera();

    void ToogleFreeCamera();

    glm::vec3 getCameraPosition();
    glm::vec3 getOffsetPositionVector();

    void moveCameraPosition(glm::vec3);
    void ToggleCameraLock();

    void getDirectionVector(glm::vec3 &Output);
    int8_t InvertCamera;

private:
    SurrealEngine       *Engine;
    TNodo           *cam;
    CTransform      *Target;
    ggDynWorld      *dynWorld;

    glm::vec3 pos_on_collision;
    glm::vec3 CameraTarget;
    glm::vec3 CurrentPosition;

    float screenW;
    float screenH;

    bool collision;

    bool LockCamera;

    void fixCameraPositionOnCollision   (glm::vec3&);
    void setPerpendicularOffsetVector   (glm::vec3&);

    double prevX, prevY;
    float t, p;

    using FunctionPTR = void (CCamera::*)();
    FunctionPTR CurrentUpdate;
};


#endif
