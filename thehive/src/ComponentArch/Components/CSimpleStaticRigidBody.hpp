#ifndef CSIMPLESTATICRIGIDBODY_H
#define CSIMPLESTATICRIGIDBODY_H

#include <ComponentArch/IComponent.hpp>
#include <btBulletCollisionCommon.h>
#include <Bullet/ggDynWorld.hpp>


class CSimpleStaticRigidBody : public IComponent {
    public:
        CSimpleStaticRigidBody(
            float x, float y, float z,
            float rx, float ry, float rz,
            float sX, float sY, float sZ
        );
        CSimpleStaticRigidBody(const CSimpleStaticRigidBody &orig) = delete;
        ~CSimpleStaticRigidBody();

    private:
        btDefaultMotionState*       myMotionState;
        btCollisionShape*           shape;
        btTransform                 transform;
        btRigidBody*                body;

        ggDynWorld* world;

};

#endif
