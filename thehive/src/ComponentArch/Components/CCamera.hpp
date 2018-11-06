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

        //  Functions of CCamera
        void updateCameraTarget(uint16_t,gg::Vector3f);
        gg::Vector3f getCameraPosition();
        gg::Vector3f getLastCameraPosition();

    private:
        CCamera();
        CCamera(const CCamera &orig) = delete;
        gg::Vector3f lastCameraPosition;
};


#endif