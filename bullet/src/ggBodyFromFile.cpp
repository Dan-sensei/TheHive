#include "ggBodyFromFile.hpp"

ggBodyFromFile::ggBodyFromFile(){}
ggBodyFromFile::~ggBodyFromFile(){}
ggBodyFromFile::ggBodyFromFile(std::string _path){
    ggDynWorld* world = Singleton<ggDynWorld>::Instance();


    fileLoader = new btBulletWorldImporter(world->getDynamicsWorld());
    if(! ( fileLoader->loadFile(_path.c_str()) ) )
        return;

    std::cout << "Get: " << _path << '\n';

    btCollisionObject* obj = fileLoader->getRigidBodyByIndex(0);
    body = btRigidBody::upcast(obj);
    world->addRigidBody(body);

    for(int i=0; i < fileLoader->getNumRigidBodies(); i++){
    	btCollisionObject* obj = fileLoader->getRigidBodyByIndex(i);
        btRigidBody* body = btRigidBody::upcast(obj);

    	// properties
        std::cout << "  shape type = " << body->getCollisionShape()->getShapeType() << '\n';
        std::cout << "  shape name = " << body->getCollisionShape()->getName() << '\n';
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
}
