#ifndef _COLLIDER_H
#define _COLLIDER_H

#include <btBulletCollisionCommon.h>
#include <Bullet/ggDynWorld.hpp>

class Collider{
    public:

    protected:
        btDefaultMotionState*       myMotionState;
        btCollisionShape*           shape;
        btTransform                 transform;
        btRigidBody*                body;

        ggDynWorld* world;

};

#endif
