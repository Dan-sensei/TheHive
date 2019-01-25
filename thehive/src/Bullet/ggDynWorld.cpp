#include "ggDynWorld.hpp"

#define FAR_RANGE_FACTOR    90.f
#define CLOSE_RANGE_FACTOR  1.f
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

ggDynWorld::ggDynWorld(){
    debugDrawer = Singleton<GLDebugDrawer>::Instance();

    Factory *fac = Singleton<Factory>::Instance();
    //debugBullet = fac->createDebugBullet(gg::Vector3f());
}
ggDynWorld::~ggDynWorld(){}

void ggDynWorld::addRigidBody(btRigidBody* body){
//void ggDynWorld::addRigidBody(btRigidBody* body,unsigned int Group,unsigned int Mask){
    //dynamicsWorld->addRigidBody(body,Group,Mask);
    dynamicsWorld->addRigidBody(body);
    //std::cout << body->getFlags() << '\n';
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

void ggDynWorld::debugRaycast(){
    gg::Color color;
    color.Alpha = 1;
    color.R = 212;
    color.G = 175;
    color.B = 55;
    Singleton<GameEngine>::Instance()->Draw3DLine(cameraPosition,raycastHitPosition,color,10);
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

void ggDynWorld::clear(){
    //remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
            // Al borrar los propios CRigidBody se hace delete de esto
			// delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}
    collisionShapes.clear();


}
void ggDynWorld::clean(){
    //remove the rigidbodies from the dynamics world and delete them
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
            // Al borrar los propios CRigidBody se hace delete de esto
			// delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	// for (int j = 0; j < collisionShapes.size(); j++)
	// {
	// 	btCollisionShape* shape = collisionShapes[j];
	// 	collisionShapes[j] = 0;
	// 	delete shape;
	// }

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

    // btBulletWorldImporter*  fileLoader = new btBulletWorldImporter(dynamicsWorld);
    // fileLoader->deleteAllData();
    // delete fileLoader;
}

void ggDynWorld::setGravity(float x, float y, float z){
    dynamicsWorld->setGravity(btVector3(x,y,z));
}

btDiscreteDynamicsWorld* ggDynWorld::getDynamicsWorld() {
    return dynamicsWorld;
}


gg::Vector3f ggDynWorld::handleRayCastTo(gg::Vector3f from, gg::Vector3f to,float _weaponRange){


    gg::Vector3f ret(-1,-1,-1);
    raycastVector           = to;
    cameraPosition          = from;
    raycastHitPosition      = ret;
    raycastCollisionBody    = nullptr;

    btCollisionWorld::ClosestRayResultCallback callBack(btVector3(from.X,from.Y,from.Z),btVector3(to.X,to.Y,to.Z));

    dynamicsWorld->rayTest(btVector3(from.X,from.Y,from.Z),btVector3(to.X,to.Y,to.Z),callBack);

    if(callBack.hasHit()){
        ret = gg::Vector3f(callBack.m_hitPointWorld.getX(),callBack.m_hitPointWorld.getY(),callBack.m_hitPointWorld.getZ());
        // <DEBUG VISUAL>
            //CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, debugBullet));
            //cTransform->setPosition(ret);
        // </DEBUG VISUAL>

        raycastHitPosition = ret;
        raycastCollisionBody = const_cast<btRigidBody*>(btRigidBody::upcast(callBack.m_collisionObject));
    }
    return ret;

}
gg::Vector3f ggDynWorld::handleRayCast(gg::Vector3f from, gg::Vector3f rot,float _weaponRange){
    if(_weaponRange == -1)  _weaponRange  = FAR_RANGE_FACTOR;
    else                    _weaponRange *= FAR_RANGE_FACTOR;

    gg::Vector3f aux = gg::Vector3f(
         sin(rot.Y  *PI/180.f)*(cos(rot.X  *PI/180.f) ) ,
        -sin(rot.X  *PI/180.f) ,
         cos(rot.Y  *PI/180.f)*(cos(rot.X  *PI/180.f) )
    );


    gg::Vector3f to =aux*FAR_RANGE_FACTOR+from;

    return handleRayCastTo(from,to,_weaponRange);


}

int ggDynWorld::getIDFromRaycast(){
    if(!raycastCollisionBody)
        return -1;
    ObjectManager* Manager = Singleton<ObjectManager>::Instance();
    return Manager->returnIDFromRigid(raycastCollisionBody);
}
void ggDynWorld::applyForceToRaycastCollisionBody(gg::Vector3f force){
    if(!raycastCollisionBody)
        return;
    raycastCollisionBody->applyCentralForce(btVector3(force.X,force.Y,force.Z));
}

gg::Vector3f ggDynWorld::getRaycastVector(){
    return raycastVector;
}

gg::Vector3f ggDynWorld::getRaycastHitPosition(){
    return raycastHitPosition;
}

bool ggDynWorld::RayCastTest(const gg::Vector3f &Start, const gg::Vector3f &End, gg::Vector3f &CollisionResult){

    btVector3 Starto = btVector3(Start.X,Start.Y,Start.Z);
    btVector3 Endo = btVector3(End.X,End.Y,End.Z);

    btCollisionWorld::ClosestRayResultCallback callBack(Starto, Endo);
    dynamicsWorld->rayTest(Starto, Endo, callBack);

    if(callBack.hasHit()){
        CollisionResult = gg::Vector3f(callBack.m_hitPointWorld.getX(),callBack.m_hitPointWorld.getY(),callBack.m_hitPointWorld.getZ());
        return true;
    }
    return false;
}

bool ggDynWorld::DoesItHitSomething(const gg::Vector3f &Start, const gg::Vector3f &End){
    btVector3 Starto = btVector3(Start.X,Start.Y,Start.Z);
    btVector3 Endo = btVector3(End.X,End.Y,End.Z);

    btCollisionWorld::ClosestRayResultCallback callBack(Starto, Endo);
    dynamicsWorld->rayTest(Starto, Endo, callBack);

    if(callBack.hasHit())   return true;

    return false;
}

bool ggDynWorld::contactTest(btCollisionObject *_obj){
    SimulationContactResultCallback callback;
    collisionWorld->contactTest(_obj,callback);
    return callback.bCollision;
}
