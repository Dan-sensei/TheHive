#include "CMeshCollider.hpp"

CMeshCollider::CMeshCollider(const std::string &BulletFile, float x, float y, float z)
{
    world = Singleton<ggDynWorld>::Instance();

    fileLoader = new btBulletWorldImporter();
    if(! ( fileLoader->loadFile(BulletFile.c_str())) ){
        return;
    }

    btCollisionObject* obj = fileLoader->getRigidBodyByIndex(0);
    body = btRigidBody::upcast(obj);
    shape = body->getCollisionShape();

    transform = obj->getWorldTransform();

    transform.setOrigin(btVector3(x,y,z));
    myMotionState = new btDefaultMotionState(transform);
    body->setMotionState(myMotionState);

    world->addShape(shape);

    btScalar mass(0);
    btVector3 localInertia;
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    body = new btRigidBody(rbInfo);

    world->addRigidBody(body);
    //world->addRigidBody(body,Group,Mask);

    // if(kinematic){
    //     // CF_KINEMATIC_OBJECT = 2
    //     body->setCollisionFlags(2);
    // }

    body->setAngularFactor(btVector3(0,0,0));
}

CMeshCollider::~CMeshCollider(){
    delete myMotionState;
    world->removeRigidBody(body);
    delete body;
    delete fileLoader;
}
