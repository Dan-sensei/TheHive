#include "CSimpleStaticRigidBody.hpp"

CSimpleStaticRigidBody::CSimpleStaticRigidBody(
    float x, float y, float z,
    float rx, float ry, float rz,
    float sX, float sY, float sZ
){
    world = Singleton<ggDynWorld>::Instance();

    shape = new btBoxShape(btVector3(btScalar(sX), btScalar(sY), btScalar(sZ)));

    transform.setIdentity();
    transform.setOrigin(btVector3(x,y,z));
    transform.setRotation(btQuaternion(rx, ry, rz, 1));
    myMotionState = new btDefaultMotionState(transform);

    world->addShape(shape);

    btScalar mass(0);
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia;

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    body = new btRigidBody(rbInfo);

    body->setFriction(btScalar(0.2));

    world->addRigidBody(body);
    body->setAngularFactor(btVector3(0,0,0));
}

CSimpleStaticRigidBody::~CSimpleStaticRigidBody(){
    delete myMotionState;
    world->removeRigidBody(body);
    delete body;
    delete shape;
}
