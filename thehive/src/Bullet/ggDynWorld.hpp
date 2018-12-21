#ifndef GGDYNWORLD_H
#define GGDYNWORLD_H

#include <cmath>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

#include <GameEngine/GameEngine.hpp>
#include <Factory.hpp>
#include <Singleton.hpp>

#include <ComponentArch/ObjectManager.hpp>

#include <Bullet/GLDebugDrawer.h>

class CTransform;

struct SimulationContactResultCallback : public btCollisionWorld::ContactResultCallback{
    bool bCollision;
    SimulationContactResultCallback():bCollision(false){}

    btScalar addSingleResult(
        btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0Wrap,
        int partId0,
        int index0,
        const btCollisionObjectWrapper* colObj1Wrap,
        int partId1,
        int index1)
    {

        gg::Vector3f vecA(
            cp.m_localPointA.getX(),
            cp.m_localPointA.getY(),
            cp.m_localPointA.getZ()
        );
        gg::Vector3f vecB(
            cp.m_localPointB.getX(),
            cp.m_localPointB.getY(),
            cp.m_localPointB.getZ()
        );
        if(cp.getDistance()<gg::DIST(vecA,vecB)){
            //If cp distance less than threshold
            bCollision = true;
        }
        return 0;
    }
};

class ggDynWorld {
public:
    ggDynWorld ();
    virtual ~ggDynWorld ();

    void inito(float=0, float=-10, float=0);

    bool handleRayCast(gg::Vector3f,gg::Vector3f, gg::Vector3f &Result, float=-1);

    void addRigidBody(btRigidBody*, unsigned int group = 1, unsigned int mask = 1);
    void addShape(btCollisionShape*);
    void stepSimulation(float, int=1, float=1./60.);
    void setGravity(float,float,float);

    btDiscreteDynamicsWorld* getDynamicsWorld();

    gg::Vector3f getRaycastVector();
    gg::Vector3f getRaycastHitPosition();
    void applyForceToRaycastCollisionBody(gg::Vector3f,gg::Vector3f);

    bool contactTest(btCollisionObject*);

    //  ---
    //  Do a ray cast test! If it hits something it will return true, and the collision point on te 3rd
    //  parameter, if not, it will return false, an it'll leave CollisionResult untouched
    //===================================================================================================
    bool RayCastTest(const gg::Vector3f &Start, const gg::Vector3f &End, gg::Vector3f &CollisionResult);

    //  ---
    //  Do a ray cast test! And just returns true or false
    //===================================================================================================
    bool DoesItHitSomething(const gg::Vector3f &Start, const gg::Vector3f &End);

    void removeRigidBody(btRigidBody*);
    void removeCollisionObject(btCollisionObject*);

    void setDebug(bool _d){debug=_d;}
    void debugDrawWorld();
    void debugRaycast();

    void printObjects(int);
    void clean();
    void clear();
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

    uint16_t debugBullet;
};




#endif
