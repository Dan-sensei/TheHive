#ifndef GGDYNWORLD_H
#define GGDYNWORLD_H

#include <cmath>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

#include <GameEngine/GameEngine.hpp>
#include <Singleton.hpp>

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/ObjectManager.hpp>

#include <Bullet/GLDebugDrawer.h>

class CTransform;

class ggDynWorld {
public:
    ggDynWorld ();
    virtual ~ggDynWorld ();

    void inito(float=0, float=-10, float=0);

    void addRigidBody(btRigidBody*);
    void addShape(btCollisionShape*);
    void stepSimulation(float, int=1, float=1./60.);
    void setGravity(float,float,float);

    btDiscreteDynamicsWorld* getDynamicsWorld();

    gg::Vector3f handleRayCast(gg::Vector3f,gg::Vector3f,float=-1);
    gg::Vector3f getRaycastVector();
    gg::Vector3f getRaycastHitPosition();
    void applyForceToRaycastCollisionBody(gg::Vector3f,gg::Vector3f);

    void removeRigidBody(btRigidBody*);
    void removeCollisionObject(btCollisionObject*);

    void setDebug(bool _d){debug=_d;}
    void debugDrawWorld();
    void debugRaycast();

    void printObjects(int);
    void clean();
private:
    bool debug;

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
    btCollisionWorld* collisionWorld;
    btIDebugDraw* debugDrawer;

    // ------------------------- //
    // IMPORTANTE: CUERPO!=FORMA //
    // ------------------------- //

    // Vector que contiene todas las 'FORMAS' (cuadrados, circulos, ...)
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    // VARIABLES
    gg::Vector3f cameraPosition;
    gg::Vector3f raycastVector;
    gg::Vector3f raycastHitPosition;
    btRigidBody* raycastCollisionBody;
};




#endif
