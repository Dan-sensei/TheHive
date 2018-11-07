#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <cstdint>
#include <cmath>

class CCamera : public IComponent {
public:
    CCamera ();
    virtual ~CCamera ();

    static void initComponent();

    void updateCameraTarget(uint16_t,gg::Vector3f,bool);
    gg::Vector3f getCameraPosition();
    gg::Vector3f getCameraTarget();

    gg::Vector3f getLastCameraPosition();
    gg::Vector3f getCameraPositionBeforeLockRotation();

private:
    gg::Vector3f lastCameraPosition;
    gg::Vector3f cameraPositionBeforeLockRotation;

};


#endif