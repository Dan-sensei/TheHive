#include "ggDynWorld.hpp"

ggDynWorld::ggDynWorld(){}
ggDynWorld::~ggDynWorld(){}

void ggDynWorld::addRigidBody(btRigidBody* body){
    dynamicsWorld->addRigidBody(body);
}

void ggDynWorld::addShape(btCollisionShape* shape){
    collisionShapes.push_back(shape);
}

void ggDynWorld::stepSimulation(float timeStep, int maxSubSteps, float fixedTimeStep){
    dynamicsWorld->stepSimulation(timeStep,maxSubSteps,fixedTimeStep);
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