#ifndef GGBODYFROMFILE_H
#define GGBODYFROMFILE_H

#include <string>
#include <iostream>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

// <NUEVO>
#include <BulletWorldImporter/btBulletWorldImporter.h>
// </NUEVO>

#include "Singleton.hpp"
#include "ggDynWorld.hpp"

class ggBodyFromFile {
public:
    ggBodyFromFile ();
    ggBodyFromFile (std::string);
    virtual ~ggBodyFromFile ();

private:
    btCollisionShape*       shape;
    btTransform             transform;
    btRigidBody*            body;
    btBulletWorldImporter*  fileLoader;
};


#endif
