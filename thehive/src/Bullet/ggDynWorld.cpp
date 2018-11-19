#include "ggDynWorld.hpp"

#define RANGE_FACTOR 90.f
#define PI 3.14159265359

ggDynWorld::ggDynWorld(){
    debugDrawer = Singleton<GLDebugDrawer>::Instance();
}
ggDynWorld::~ggDynWorld(){}

void ggDynWorld::addRigidBody(btRigidBody* body){
    dynamicsWorld->addRigidBody(body);
}

void ggDynWorld::removeRigidBody(btRigidBody *body){
    dynamicsWorld->removeRigidBody(body);
}

void ggDynWorld::removeCollisionObject(btCollisionObject *obj){
    dynamicsWorld->removeCollisionObject(obj);
}

void ggDynWorld::addShape(btCollisionShape* shape){
    collisionShapes.push_back(shape);
}

void ggDynWorld::stepSimulation(float timeStep, int maxSubSteps, float fixedTimeStep){
    dynamicsWorld->stepSimulation(timeStep,maxSubSteps,fixedTimeStep);

    // dynamicsWorld->updateAabbs();
    // dynamicsWorld->computeOverlappingPairs();
}

void ggDynWorld::debugDrawWorld(){
    if(debug){
        debugDrawer->setDebugMode(1);
        dynamicsWorld->setDebugDrawer(debugDrawer);
        dynamicsWorld->debugDrawWorld();
    }
}

void ggDynWorld::printObjects(int _end){
	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= _end; j--){
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;

		if (body && body->getMotionState())
			body->getMotionState()->getWorldTransform(trans);
		else
			trans = obj->getWorldTransform();

		printf("OBJETO %d | POSICION = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
}

void ggDynWorld::inito(float _gX, float _gY, float _gZ){
    collisionConfiguration  = new btDefaultCollisionConfiguration();
    dispatcher              = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache    = new btDbvtBroadphase();
    solver                  = new btSequentialImpulseConstraintSolver;
    dynamicsWorld           = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    collisionWorld          = new btCollisionWorld(dispatcher, overlappingPairCache, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(_gX, _gY, _gZ));
}

void ggDynWorld::clean(){
    //remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();
}

void ggDynWorld::setGravity(float x, float y, float z){
    dynamicsWorld->setGravity(btVector3(x,y,z));
}

btDiscreteDynamicsWorld* ggDynWorld::getDynamicsWorld() {
    return dynamicsWorld;
}

gg::Vector3f ggDynWorld::handleRayCast(gg::Vector3f from, gg::Vector3f rot){
    // from -> Camera position
    // to   -> Camera rotation
    gg::Vector3f ret(-1,-1,-1);
    gg::Vector3f to = gg::Vector3f(
        (sin(rot.Y*PI/180)*RANGE_FACTOR)+from.X,
        -(sin(rot.X*PI/180)*RANGE_FACTOR)+from.Y,
        (cos(rot.X*PI/180)*cos(rot.Y*PI/180)*RANGE_FACTOR)+from.Z
    );

    btCollisionWorld::ClosestRayResultCallback callBack(btVector3(from.X,from.Y,from.Z),btVector3(to.X,to.Y,to.Z));

    dynamicsWorld->rayTest(btVector3(from.X,from.Y,from.Z),btVector3(to.X,to.Y,to.Z),callBack);

    if(callBack.hasHit()){
        // printf("Collision at: <%.2f, %.2f, %.2f>\n", callBack.m_hitPointWorld.getX(), callBack.m_hitPointWorld.getY(), callBack.m_hitPointWorld.getZ());
    // <DEBUG VISUAL>
        // CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, 4));
        // cTransform->setPosition(gg::Vector3f(callBack.m_hitPointWorld.getX(),callBack.m_hitPointWorld.getY(),callBack.m_hitPointWorld.getZ()));
    // </DEBUG VISUAL>

        ret = gg::Vector3f(callBack.m_hitPointWorld.getX(),callBack.m_hitPointWorld.getY(),callBack.m_hitPointWorld.getZ());

    }
    return ret;
}

gg::Vector3f ggDynWorld::handleRayCastWithoutCollision(gg::Vector3f from, gg::Vector3f rot){
    // from -> Camera position
    // to   -> Camera rotation
    gg::Vector3f to = gg::Vector3f(
        (sin(rot.Y*PI/180)*RANGE_FACTOR)+from.X,
        -(sin(rot.X*PI/180)*RANGE_FACTOR)+from.Y,
        (cos(rot.X*PI/180)*cos(rot.Y*PI/180)*RANGE_FACTOR)+from.Z
    );

    return to;
}
