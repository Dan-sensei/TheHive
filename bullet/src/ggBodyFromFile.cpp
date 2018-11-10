#include "ggBodyFromFile.hpp"

ggBodyFromFile::ggBodyFromFile(){}
ggBodyFromFile::~ggBodyFromFile(){}
ggBodyFromFile::ggBodyFromFile(std::string _path){
    ggDynWorld* world = Singleton<ggDynWorld>::Instance();

    std::cout << "Get: " << _path << '\n';

    fileLoader = new btBulletWorldImporter(world->getDynamicsWorld());
    fileLoader->loadFile(_path.c_str());

    for(int i=0; i < fileLoader->getNumRigidBodies(); i++){
    	btCollisionObject* obj = fileLoader->getRigidBodyByIndex(i);
    	btRigidBody* body = btRigidBody::upcast(obj);

    	// properties
    	printf("  object name = %s\n", fileLoader->getNameForPointer(body));	// The Blender object name
        printf("  get position = (%4.3f,%4.3f,%4.3f)\n",
    		body->getCenterOfMassPosition().getX(),
    		body->getCenterOfMassPosition().getY(),
    		body->getCenterOfMassPosition().getZ());			// Blender CoM
    	printf("  get local scaling = (%4.3f,%4.3f,%4.3f)\n",
    		body->getCollisionShape()->getLocalScaling().getX(),
    		body->getCollisionShape()->getLocalScaling().getY(),
    		body->getCollisionShape()->getLocalScaling().getZ());		// Blender Dimensions

        if (body->getInvMass() == 0)
    		printf("  static object\n");
    	else{
    		printf("  mass = %4.3f\n", 1/body->getInvMass());		// Blender Mass
    		printf("  get gravity (z!) = %4.3f\n", body->getGravity().getZ());	// Blender Gravity
    	}
    	printf("\n");
    }













    // // AQUI SE DEFINEN LAS DIMENSIONES
    // shape = new btBoxShape(btVector3(btScalar(_sX), btScalar(_sY), btScalar(_sZ)));
    //
    // // Hago push_back en el vector de 'shapes'
    // world->addShape(shape);
    //
    // // AQUI SE DEFINE LA POSICION
    // transform.setIdentity();
    // transform.setOrigin(btVector3(_x,_y,_z));
    //
    // // MASS!=0 ---> RIGIDBODY ES DINAMICO
    // // MASS==0 ---> RIGIDBODY ES ESTATICO
    // btScalar mass(_mass);
    // bool isDynamic = (mass != 0.f);
    // btVector3 localInertia(_iX,_iY,_iZ);
    // if (isDynamic)
    //     shape->calculateLocalInertia(mass, localInertia);
    //
    // // Supongo que es algo que mejora las colisiones y opcional, PERO, sin el myMotionState NO SE PUEDE INICIALIZAR EL BODY =D
    //     // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    // btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
    // btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    // body = new btRigidBody(rbInfo);
    //
    // // Add the body to the dynamics world
    // world->addRigidBody(body);
}