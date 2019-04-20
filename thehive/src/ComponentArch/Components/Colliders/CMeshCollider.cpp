#include "CMeshCollider.hpp"

CMeshCollider::CMeshCollider(const std::string &BulletFile, float x, float y, float z)
:MeshColliderHelper(BulletFile, x, y, z),
 myMotionState(transform)
{
    btCollisionObject* obj = fileLoader.getRigidBodyByIndex(0);
    btRigidBody* body_mesh = btRigidBody::upcast(obj);
    body_mesh->setMotionState(&myMotionState);
    world->setGravity(0,-15,0);
    
}

CMeshCollider::~CMeshCollider(){
    fileLoader.deleteAllData();
}
