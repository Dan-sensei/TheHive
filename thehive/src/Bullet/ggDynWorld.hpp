#ifndef GGDYNWORLD_H
#define GGDYNWORLD_H

#include <cmath>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

#include <Factory.hpp>
#include <Singleton.hpp>

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/ObjectManager.hpp>

#include <Bullet/GLDebugDrawer.h>

#include <ComponentArch/Components/CRigidBody.hpp>
class CRigidBody;

struct SimulationContactResultCallback : public btCollisionWorld::ContactResultCallback{
    bool bCollision;
    btCollisionObject *exclude;

    SimulationContactResultCallback():bCollision(false),exclude(nullptr){}
    SimulationContactResultCallback(btCollisionObject *obj):bCollision(false),exclude(nullptr){
        if(obj) exclude = obj;
    }

    btScalar addSingleResult(
        btManifoldPoint& cp,
        const btCollisionObjectWrapper* colObj0Wrap,
        int partId0,
        int index0,
        const btCollisionObjectWrapper* colObj1Wrap,
        int partId1,
        int index1)
    {
        glm::vec3 vecA(
            cp.m_localPointA.getX(),
            cp.m_localPointA.getY(),
            cp.m_localPointA.getZ()
        );
        glm::vec3 vecB(
            cp.m_localPointB.getX(),
            cp.m_localPointB.getY(),
            cp.m_localPointB.getZ()
        );
        if(cp.getDistance()<glm::distance(vecA,vecB)){
            //If cp distance less than threshold
            if(exclude){
                if(exclude != colObj1Wrap->m_collisionObject){
                    bCollision = true;
                }
            }
            else{
                bCollision = true;
            }
        }
        return 0;
    }
};

class ggDynWorld {
public:
    ggDynWorld ();
    virtual ~ggDynWorld ();

    void inito(float=0, float=-10, float=0);

    void addRigidBody(btRigidBody*);
    int getIDFromRaycast();

    //void addRigidBody(btRigidBody*,unsigned int Group=0,unsigned int Mask=0);
    void addShape(btCollisionShape*);
    void stepSimulation(float, int=1, float=1./60.);
    void setGravity(float,float,float);

    btDiscreteDynamicsWorld* getDynamicsWorld();

    glm::vec3 handleRayCast(glm::vec3,glm::vec3,float=-1);
    glm::vec3 handleRayCastTo(glm::vec3,glm::vec3,float=1000);

    glm::vec3 getRaycastVector();
    glm::vec3 getRaycastHitPosition();
    void applyForceToRaycastCollisionBody(glm::vec3);

    bool contactTest(btCollisionObject*);
    bool contactTest(btCollisionObject *objA, btCollisionObject *objB);

    //  ---
    //  Do a ray cast test! If it hits something it will return true, and the collision point on te 3rd
    //  parameter, if not, it will return false, an it'll leave CollisionResult untouched
    //===================================================================================================
    bool RayCastTest(const glm::vec3 &Start, const glm::vec3 &End, glm::vec3 &CollisionResult);
    bool RayCastTest(const glm::vec3 &Start, const glm::vec3 &End, glm::vec3 &CollisionResult, CRigidBody *ExcludeA = nullptr, CRigidBody *ExcludeB = nullptr);
    bool CompleteRayCastTest(const glm::vec3 &Start, const glm::vec3 &End, glm::vec3 &CollisionResult, CRigidBody *ExcludeA = nullptr, CRigidBody *ExcludeB = nullptr);

    //  ---
    //  Do a ray cast test! And just returns true or false
    //===================================================================================================
    bool DoesItHitSomething(const glm::vec3 &Start, const glm::vec3 &End);

    void removeRigidBody(btRigidBody*);
    void removeCollisionObject(btCollisionObject*);

    void setDebug(bool _d){debug=_d;}
    void debugDrawWorld();
    void debugRaycast();

    //void printObjects(int);
    void clean();
    void clear();

private:
    // Contiene la configuracion por defecto para las colisiones
    // Es modificable arrobaDani
    btDefaultCollisionConfiguration collisionConfiguration;
    //
    btCollisionDispatcher dispatcher;
    // Algo parecido al SAT pero mucho mejor
    // btBroadphaseInterface overlappingPairCache;
    btDbvtBroadphase overlappingPairCache;
    //
    btSequentialImpulseConstraintSolver solver;
    // El mundo donde pasan los eventos
    // Ademas, tiene una lista de TODOS los cuerpos
    btDiscreteDynamicsWorld dynamicsWorld;

private:
    btCollisionWorld collisionWorld;
    bool debug;





    // btIDebugDraw* debugDrawer;

    // ------------------------- //
    // IMPORTANTE: CUERPO!=FORMA //
    // ------------------------- //

    // Vector que contiene todas las 'FORMAS' (cuadrados, circulos, ...)
    btAlignedObjectArray<btCollisionShape*> collisionShapes;

    // VARIABLES
    glm::vec3 cameraPosition;
    glm::vec3 raycastVector;
    glm::vec3 raycastHitPosition;
    btRigidBody* raycastCollisionBody;

    uint16_t debugBullet;
};




#endif
