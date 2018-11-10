#ifndef GGDYNWORLD_H
#define GGDYNWORLD_H

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

class ggDynWorld {
public:
    ggDynWorld ();
    virtual ~ggDynWorld ();

    void inito(float=0, float=-10, float=0);

    void addRigidBody(btRigidBody*);
    void addShape(btCollisionShape*);
    void stepSimulation(float, int=1, float=1./60.);

    void printObjects(int);
    void clean();
private:
    // Contiene la configuracion por defecto para las colisiones
    // Es modificable arrobaDani
    btDefaultCollisionConfiguration* collisionConfiguration;

    //
    btCollisionDispatcher* dispatcher;

    // Algo parecido al SAT pero mucho mejor
    btBroadphaseInterface* overlappingPairCache;

    //
    btSequentialImpulseConstraintSolver* solver;

    // El mundo donde pasan los eventos
    // Ademas, tiene una lista de TODOS los cuerpos
    btDiscreteDynamicsWorld* dynamicsWorld;

    // ------------------------- //
    // IMPORTANTE: CUERPO!=FORMA //
    // ------------------------- //

    // Vector que contiene todas las 'FORMAS' (cuadrados, circulos, ...)
    btAlignedObjectArray<btCollisionShape*> collisionShapes;


};




#endif