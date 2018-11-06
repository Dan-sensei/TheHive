#ifndef _CCAMERA_H
#define _CCAMERA_H

#include <ComponentArch/IComponent.hpp>
#include <cstdint>
#include <cmath>

class CCamera : public IComponent {
    friend class ObjectManager;
    public:
        virtual ~CCamera ();

        static void initComponent();

        void updateCameraTarget(uint16_t,gg::Vector3f);
        gg::Vector3f getCameraPosition();
    private:
        CCamera();
        CCamera(const CCamera &orig) = delete;

};


#endif