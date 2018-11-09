#ifndef GGRIGIDBODY_H
#define GGRIGIDBODY_H

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

#include "Singleton.hpp"
#include "ggDynWorld.hpp"

class ggRigidBody {
public:
    ggRigidBody ();
    ggRigidBody (
        float=0, float=0, float=0,  // Origen   x,y,z
        float=1, float=1, float=1,  // Tamanyo  x,y,z
        float=1,                    // Masa     w
        float=0, float=0, float=0   // Inercia  vX,vY,vZ
    );
    virtual ~ggRigidBody ();

private:
    btCollisionShape*   shape;
    btTransform         transform;
    btRigidBody*        body;

};


#endif