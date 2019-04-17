#ifndef _CBOXCOLLIDER_H
#define _CBOXCOLLIDER_H

#include <ComponentArch/IComponent.hpp>
#include "Collider.hpp"

class CBoxCollider : public IComponent, public Collider {
    public:
        CBoxCollider(
            float x, float y, float z,
            float rx, float ry, float rz, float rw,
            float sX, float sY, float sZ
        );

        void setToKinematic();
        void setToStatic();

        CBoxCollider(const CBoxCollider &orig) = delete;
        ~CBoxCollider();

    private:
};

#endif
