#include "ggRigidBody.hpp"

ggRigidBody::ggRigidBody(){}
ggRigidBody::~ggRigidBody(){}
ggRigidBody::ggRigidBody(
    float _x,   float _y,   float _z,   // Origen
    float _sX,  float _sY,  float _sZ,  // Tamayo
    float _mass,                        // Masa
    float _iX,  float _iY,  float _iZ   // Inercia
){
    ggDynWorld* world = Singleton<ggDynWorld>::Instance();

    // AQUI SE DEFINEN LAS DIMENSIONES
    shape = new btBoxShape(btVector3(btScalar(_sX), btScalar(_sY), btScalar(_sZ)));

    // Hago push_back en el vector de 'shapes'
    world->addShape(shape);

    // AQUI SE DEFINE LA POSICION
    transform.setIdentity();
    transform.setOrigin(btVector3(_x,_y,_z));

    // MASS!=0 ---> RIGIDBODY ES DINAMICO
    // MASS==0 ---> RIGIDBODY ES ESTATICO
    btScalar mass(_mass);
    bool isDynamic = (mass != 0.f);
    btVector3 localInertia(_iX,_iY,_iZ);
    if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);

    // Supongo que es algo que mejora las colisiones y opcional, PERO, sin el myMotionState NO SE PUEDE INICIALIZAR EL BODY =D
        // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    body = new btRigidBody(rbInfo);

    // Add the body to the dynamics world
    world->addRigidBody(body);
}