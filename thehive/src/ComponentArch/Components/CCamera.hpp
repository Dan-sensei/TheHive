#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <cstdint>
#include <cmath>
#include <SurrealEngine/TMotorTAG.hpp>
#include <SurrealEngine/TNodo.hpp>
#include <Singleton.hpp>

#include "CTransform.hpp"
#include <ComponentArch/ObjectManager.hpp>

class CRigidBody;
class ggDynWorld;
class CCamera : public IComponent {
friend class Factory;
public:
    CCamera(bool);
    CCamera(const CCamera &orig) = delete;
    virtual ~CCamera ();

    // Functions of IComponent
    virtual void Init();

    void setTarget(CTransform* T);
    void CameraUpdate();

    glm::vec3 getCameraPosition();
    glm::vec3 getCameraRotation();
    glm::vec3 getOffsetPositionVector();

    void moveCameraPosition(glm::vec3);

    glm::vec3 getlastHeroPosition();
    glm::vec3 getCameraPositionBeforeLockRotation();
    void setCameraPositionBeforeLockRotation(glm::vec3); // Por ahora no se usa

private:
    CRigidBody      *CRigidbody;
    TMotorTAG       *Engine;
    ObjectManager   *Manager;
    TNodo           *cam;
    CTransform      *Target;
    ggDynWorld      *dynWorld;

    glm::vec3 lastHeroPosition;
    glm::vec3 cameraPositionBeforeLockRotation;
    glm::vec3 offsetPositionVector;
    glm::vec3 pos_on_collision;
    glm::vec3 last_cam_position;

    glm::vec3 Pos;
    glm::vec3 Rot;

    float screenW;
    float screenH;

    bool daniNoSabeProgramar;
    bool collision;

    void getNewRotation                 (glm::vec3&);
    void setFinalRotation               (glm::vec3&,glm::vec3&,bool);
    void setHorizontalAxis              (glm::vec3&,glm::vec3&,glm::vec3&,glm::vec3&);
    void setVerticalAxis                (glm::vec3&,glm::vec3&,glm::vec3&, glm::vec3&);
    void fixCameraPositionOnCollision   (glm::vec3&);
    void setPerpendicularOffsetVector   (glm::vec3&);

};


#endif
