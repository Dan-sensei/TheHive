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

    void getDirectionVector(glm::vec3 &Output);

private:
    TMotorTAG       *Engine;
    TNodo           *cam;
    CTransform      *Target;
    ggDynWorld      *dynWorld;

    glm::vec3 pos_on_collision;

    glm::vec3 CurrentPosition;
    glm::vec3 Rot;

    float screenW;
    float screenH;

    int8_t InvertCamera;
    bool collision;

    void fixCameraPositionOnCollision   (glm::vec3&);
    void setPerpendicularOffsetVector   (glm::vec3&);

    double prevX, prevY;
    float t, p;

};


#endif
