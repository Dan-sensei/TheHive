#include "CBoxCollider.hpp"

CBoxCollider::CBoxCollider(
    float x, float y, float z,
    float rx, float ry, float rz, float rw,
    float sX, float sY, float sZ
)
:BoxColliderHelper(x,y,z,rx,ry,rz,rw),
 shape(btVector3(btScalar(sX), btScalar(sY), btScalar(sZ))),
 myMotionState(transform),
 body(0, &myMotionState, &shape)
{
    body.setFriction(btScalar(0.2));
    world->addRigidBody(&body);
    body.setAngularFactor(btVector3(0,0,0));
    world->setGravity(0,-15,0);
    
}

CBoxCollider::~CBoxCollider(){
    world->removeRigidBody(&body);
}

void CBoxCollider::setToKinematic(){
    body.setCollisionFlags(2);
}
void CBoxCollider::setToStatic(){
    body.setCollisionFlags(1);
}
