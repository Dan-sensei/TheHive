#ifndef _COLLIDER_HELPERS_H
#define _COLLIDER_HELPERS_H

#include <btBulletCollisionCommon.h>
#include <Bullet/ggDynWorld.hpp>

struct World{
    World();
    ggDynWorld* world;
};

class BoxColliderHelper : public World {
    public:
        BoxColliderHelper(
            float x, float y, float z,
            float rx, float ry, float rz, float rw
        );

    protected:
        btTransform                 transform;
};

class MeshColliderHelper : public World{
    public:
        MeshColliderHelper(const std::string &BulletFile, float x, float y, float z);

    protected:
        btBulletWorldImporter       fileLoader;
        btTransform                 transform;
};

#endif
