#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <cstdint>
#include <cmath>

class CCamera : public IComponent {
friend class ObjectManager;
public:
    virtual ~CCamera ();

    // Functions of IComponent
    static void initComponent();
    virtual void initializeComponentData(const void* data);
    virtual void initAfterComponentAssigment();

    void updateCameraTarget(uint16_t,gg::Vector3f,bool);
    gg::Vector3f getCameraPosition();
    gg::Vector3f getCameraTarget();

    gg::Vector3f getLastCameraPosition();
    gg::Vector3f getCameraPositionBeforeLockRotation();

private:
    CCamera();
    gg::Vector3f lastCameraPosition;
    gg::Vector3f cameraPositionBeforeLockRotation;

};


#endif