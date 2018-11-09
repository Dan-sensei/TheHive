/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

///-----includes_start-----
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <stdio.h>

/// This is a Hello World program for running a basic Bullet physics simulation

int main(int argc, char** argv)
{
	///-----includes_end-----
	int i;

    // <INICIALIZACION>
        // Contiene la configuracion por defecto para la memoria y colisiones
        // Se puede MODIFICAR
    	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

        // Dispatcher por defecto
        // For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    	// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

    	// The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    	dynamicsWorld->setGravity(btVector3(0, -10, 0));
    // </INICIALIZACION>

    // Vector que tiene todas las 'shapes'
        // Keep track of the shapes, we release memory at exit.
        // Make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	//the ground is a cube of side 100 at position y = -56.
	//the sphere will hit it at y = -6, with center at -5
	{
        // Supongo que es 50x50x50
        //     - 50 de ancho
        //     - 50 de alto
        //     - 50 de largo
        // AQUI SE DEFINEN LAS DIMENSIONES
        // Es un cubo de lado 50
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

        // Hago push_back en el vector de 'shapes'
		collisionShapes.push_back(groundShape);

        // AQUI SE DEFINE LA POSICION
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -56, 0));

        // MASS!=0 ---> RIGIDBODY ES DINAMICO
        // MASS==0 ---> RIGIDBODY ES ESTATICO
        btScalar mass(0.);
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		// Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		// Add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}

	{
        // Cubo de lado 1
		btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		// btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
        startTransform.setOrigin(btVector3(2, 10, 0));

        // Objeto dinámico
        // La masa es 1
		btScalar mass(1.f);
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);


		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamicsWorld->addRigidBody(body);
	}





	/// Do some simulation

	///-----stepsimulation_start-----
	for (i = 0; i < 200; i++){
		dynamicsWorld->stepSimulation(1.f / 60.f, 10);

		//print positions of all objects
		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--){
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

	///-----stepsimulation_end-----

	//cleanup in the reverse order of creation/initialization

	///-----cleanup_start-----

	//remove the rigidbodies from the dynamics world and delete them
	for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
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
