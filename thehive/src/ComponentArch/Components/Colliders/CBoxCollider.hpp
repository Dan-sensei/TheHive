#ifndef _CBOXCOLLIDER_H
#define _CBOXCOLLIDER_H

#include <ComponentArch/IComponent.hpp>
#include "ColliderHelpers.hpp"

class CBoxCollider : public IComponent, public BoxColliderHelper {
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
        btBoxShape shape;
        btDefaultMotionState  myMotionState;
        btRigidBody body;


};

#endif
