#include "ColliderHelpers.hpp"

World::World(){
    world = Singleton<ggDynWorld>::Instance();
}

BoxColliderHelper::BoxColliderHelper(
    float x, float y, float z,
    float rx, float ry, float rz, float rw
){
    transform.setIdentity();
    transform.setOrigin(btVector3(x,y,z));
    transform.setRotation(btQuaternion(rx, ry, rz, rw));
}


MeshColliderHelper::MeshColliderHelper(
    const std::string &BulletFile, float x, float y, float z
)
:fileLoader(world->getDynamicsWorld())
{
    if(! ( fileLoader.loadFile(BulletFile.c_str())) ){
        return;
    }

    btCollisionObject* obj = fileLoader.getRigidBodyByIndex(0);
    transform = obj->getWorldTransform();
    transform.setOrigin(btVector3(x,y,z));
}