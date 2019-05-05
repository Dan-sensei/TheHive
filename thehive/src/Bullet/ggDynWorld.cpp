#include "ggDynWorld.hpp"
#include <Omicron/Omicron.hpp>

#define FAR_RANGE_FACTOR    90.f
#define CLOSE_RANGE_FACTOR  1.f
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

ggDynWorld::ggDynWorld()
:collisionConfiguration(),
 dispatcher(&collisionConfiguration),
 overlappingPairCache(),
 solver(),
 dynamicsWorld(&dispatcher, &overlappingPairCache, &solver, &collisionConfiguration),
 collisionWorld(&dispatcher, &overlappingPairCache, &collisionConfiguration)
{
    debugDrawer = Singleton<GLDebugDrawer>::Instance();
    Factory *fac = Singleton<Factory>::Instance();

    //collisionConfiguration  = new btDefaultCollisionConfiguration();
    //dispatcher              = new btCollisionDispatcher(collisionConfiguration);
    //overlappingPairCache    = new btDbvtBroadphase();
    //solver                  = new btSequentialImpulseConstraintSolver;
    //dynamicsWorld           = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    //collisionWorld          = new btCollisionWorld(dispatcher, overlappingPairCache, collisionConfiguration);

}
ggDynWorld::~ggDynWorld(){}

void ggDynWorld::addRigidBody(btRigidBody* body){
//void ggDynWorld::addRigidBody(btRigidBody* body,unsigned int Group,unsigned int Mask){
    //dynamicsWorld.addRigidBody(body,Group,Mask);
    dynamicsWorld.addRigidBody(body);
    ////std::cout << body->getFlags() << '\n';
}

void ggDynWorld::removeRigidBody(btRigidBody *body){
    dynamicsWorld.removeRigidBody(body);
}

void ggDynWorld::removeCollisionObject(btCollisionObject *obj){
    dynamicsWorld.removeCollisionObject(obj);
}

void ggDynWorld::addShape(btCollisionShape* shape){
    collisionShapes.push_back(shape);
}

void ggDynWorld::stepSimulation(float timeStep, int maxSubSteps, float fixedTimeStep){
    dynamicsWorld.stepSimulation(timeStep,maxSubSteps,fixedTimeStep);

    // dynamicsWorld.updateAabbs();
    // dynamicsWorld.computeOverlappingPairs();
}

void ggDynWorld::debugDrawWorld(){
    if(debug){
        debugDrawer->setDebugMode(1);
        dynamicsWorld.setDebugDrawer(debugDrawer);
        dynamicsWorld.debugDrawWorld();
    }
}

void ggDynWorld::debugRaycast(){
    gg::Color color;
    color.Alpha = 1;
    color.R = 212;
    color.G = 175;
    color.B = 55;
    Singleton<Omicron>::Instance()->Draw3DLine(cameraPosition,raycastHitPosition,color);
}

// void ggDynWorld::printObjects(int _end){
// 	for (int j = dynamicsWorld.getNumCollisionObjects() - 1; j >= _end; j--){
// 		btCollisionObject* obj = dynamicsWorld.getCollisionObjectArray()[j];
// 		btRigidBody* body = btRigidBody::upcast(obj);
// 		btTransform trans;
//
// 		if (body && body->getMotionState())
// 			body->getMotionState()->getWorldTransform(trans);
// 		else
// 			trans = obj->getWorldTransform();
//
// 		printf("OBJETO %d | POSICION = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
// 	}
// }

void ggDynWorld::inito(float _gX, float _gY, float _gZ){

    dynamicsWorld.setGravity(btVector3(_gX, _gY, _gZ));
}

void ggDynWorld::clear(){
    //remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld.getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld.getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
            // Al borrar los propios CRigidBody se hace delete de esto
			// delete body->getMotionState();
		}
		dynamicsWorld.removeCollisionObject(obj);
		delete obj;
	}
    collisionShapes.clear();


}
void ggDynWorld::clean(){
    //remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld.getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld.getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
            // Al borrar los propios CRigidBody se hace delete de esto
			// delete body->getMotionState();
		}
		dynamicsWorld.removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	// for (int j = 0; j < collisionShapes.size(); j++)
	// {
	// 	btCollisionShape* shape = collisionShapes[j];
	// 	collisionShapes[j] = 0;
	// 	delete shape;
	// }

	// //delete dynamics world
	// delete dynamicsWorld;
    //
	// //delete solver
	// delete solver;
    //
	// //delete broadphase
	// delete overlappingPairCache;
    //
	// //delete dispatcher
	// delete dispatcher;
    //
	// delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();

    // btBulletWorldImporter*  fileLoader = new btBulletWorldImporter(dynamicsWorld);
    // fileLoader->deleteAllData();
    // delete fileLoader;
}

void ggDynWorld::setGravity(float x, float y, float z){
    dynamicsWorld.setGravity(btVector3(x,y,z));
}

btDiscreteDynamicsWorld* ggDynWorld::getDynamicsWorld() {
    return &dynamicsWorld;
}


glm::vec3 ggDynWorld::handleRayCastTo(glm::vec3 from, glm::vec3 to,float _weaponRange){


    glm::vec3 ret(-1,-1,-1);
    raycastVector           = to;
    cameraPosition          = from;
    raycastHitPosition      = ret;
    raycastCollisionBody    = nullptr;

    btCollisionWorld::ClosestRayResultCallback callBack(btVector3(from.x,from.y,from.z),btVector3(to.x,to.y,to.z));

    dynamicsWorld.rayTest(btVector3(from.x,from.y,from.z),btVector3(to.x,to.y,to.z),callBack);

    if(callBack.hasHit()){
        ret = glm::vec3(callBack.m_hitPointWorld.getX(),callBack.m_hitPointWorld.getY(),callBack.m_hitPointWorld.getZ());
        // <DEBUG VISUAL>
            //CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, debugBullet));
            //cTransform->setPosition(ret);
        // </DEBUG VISUAL>

        raycastHitPosition = ret;
        raycastCollisionBody = const_cast<btRigidBody*>(btRigidBody::upcast(callBack.m_collisionObject));
    }
    return ret;

}
glm::vec3 ggDynWorld::handleRayCast(glm::vec3 from, glm::vec3 Target,float _weaponRange){
    if(_weaponRange == -1)  _weaponRange  = FAR_RANGE_FACTOR;
    else                    _weaponRange *= FAR_RANGE_FACTOR;

    glm::vec3 aux = Target - from;

    glm::vec3 to =aux*FAR_RANGE_FACTOR+from;

    return handleRayCastTo(from,to,_weaponRange);


}

int ggDynWorld::getIDFromRaycast(){
    if(!raycastCollisionBody)
        return -1;
    ObjectManager* Manager = Singleton<ObjectManager>::Instance();
    return Manager->returnIDFromRigid(raycastCollisionBody);
}
void ggDynWorld::applyForceToRaycastCollisionBody(glm::vec3 force){
    if(!raycastCollisionBody)
        return;
    raycastCollisionBody->applyCentralForce(btVector3(force.x,force.y,force.z));
}

glm::vec3 ggDynWorld::getRaycastVector(){
    return raycastVector;
}

glm::vec3 ggDynWorld::getRaycastHitPosition(){
    return raycastHitPosition;
}

bool ggDynWorld::RayCastTest(const glm::vec3 &Start, const glm::vec3 &End, glm::vec3 &CollisionResult){
    btVector3 Starto = btVector3(Start.x,Start.y,Start.z);
    btVector3 Endo = btVector3(End.x,End.y,End.z);

    btCollisionWorld::ClosestRayResultCallback callBack(Starto, Endo);
    dynamicsWorld.rayTest(Starto, Endo, callBack);

    if(callBack.hasHit()){
        CollisionResult = glm::vec3(callBack.m_hitPointWorld.getX(),callBack.m_hitPointWorld.getY(),callBack.m_hitPointWorld.getZ());
        return true;
    }
    return false;
}

bool ggDynWorld::RayCastTest(const glm::vec3 &Start, const glm::vec3 &End, glm::vec3 &CollisionResult, CRigidBody *Exclude){
    btVector3 Starto = btVector3(Start.x,Start.y,Start.z);
    btVector3 Endo = btVector3(End.x,End.y,End.z);

    btCollisionWorld::ClosestRayResultCallback callBack(Starto,Endo);
    dynamicsWorld.rayTest(Starto, Endo, callBack);

    if(Exclude && callBack.m_collisionObject){
        if(callBack.m_collisionObject == Exclude->getBody()){
            return false;
        }
    }

    if(callBack.hasHit()){
        CollisionResult = glm::vec3(callBack.m_hitPointWorld.getX(),callBack.m_hitPointWorld.getY(),callBack.m_hitPointWorld.getZ());
        return true;
    }
    return false;
}


bool ggDynWorld::DoesItHitSomething(const glm::vec3 &Start, const glm::vec3 &End){
    btVector3 Starto = btVector3(Start.x,Start.y,Start.z);
    btVector3 Endo = btVector3(End.x,End.y,End.z);

    btCollisionWorld::ClosestRayResultCallback callBack(Starto, Endo);
    dynamicsWorld.rayTest(Starto, Endo, callBack);

    if(callBack.hasHit())   return true;

    return false;
}

bool ggDynWorld::contactTest(btCollisionObject *_obj){
    SimulationContactResultCallback callback;
    collisionWorld.contactTest(_obj,callback);
    return callback.bCollision;
}
