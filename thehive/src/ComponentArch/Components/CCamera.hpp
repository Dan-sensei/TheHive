#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <cstdint>
#include <cmath>
#include <SurrealEngine/SurrealEngine.hpp>
#include <SurrealEngine/TNodo.hpp>
#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>

#include "CTransform.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include "CStaticModel.hpp"

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
    ObjectManager *Manager;

    CTransform* Near;
    CStaticModel* Near_m;
    CTransform* Far;
    CStaticModel* Far_m;

    glm::vec3 pos_on_collision;
    glm::vec3 CameraTarget;
    glm::vec3 CurrentPosition;

    glm::vec3 PlanePosFar;
    glm::vec3 PlanePosNear;
    glm::vec3 cameradir;
    glm::vec3 auxPos;
    bool key_toggle;
    bool key_toggle2;
    bool visibility;
    bool visibility2;

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
