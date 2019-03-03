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

    gg::Vector3f getCameraPosition();
    gg::Vector3f getCameraRotation();
    gg::Vector3f getOffsetPositionVector();

    void moveCameraPosition(gg::Vector3f);

    gg::Vector3f getlastHeroPosition();
    gg::Vector3f getCameraPositionBeforeLockRotation();
    void setCameraPositionBeforeLockRotation(gg::Vector3f); // Por ahora no se usa

private:
    CRigidBody      *CRigidbody;
    TMotorTAG       *Engine;
    ObjectManager   *Manager;
    TNodo           *cam;
    CTransform      *Target;
    ggDynWorld      *dynWorld;

    gg::Vector3f lastHeroPosition;
    gg::Vector3f cameraPositionBeforeLockRotation;
    gg::Vector3f offsetPositionVector;
    gg::Vector3f pos_on_collision;
    gg::Vector3f last_cam_position;

    gg::Vector3f Pos;
    gg::Vector3f Rot;

    float screenW;
    float screenH;

    bool daniNoSabeProgramar;
    bool collision;

    void getNewRotation                 (gg::Vector3f&);
    void setFinalRotation               (gg::Vector3f&,gg::Vector3f&,bool);
    void setHorizontalAxis              (gg::Vector3f&,gg::Vector3f&,gg::Vector3f&,gg::Vector3f&);
    void setVerticalAxis                (gg::Vector3f&,gg::Vector3f&,gg::Vector3f&, gg::Vector3f&);
    void fixCameraPositionOnCollision   (gg::Vector3f&);
    void setPerpendicularOffsetVector   (gg::Vector3f&);

};


#endif
