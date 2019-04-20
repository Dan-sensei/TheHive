#ifndef _CMESHCOLLIDER_H
#define _CMESHCOLLIDER_H

#include <ComponentArch/IComponent.hpp>
#include "ColliderHelpers.hpp"
#include <BulletWorldImporter/btBulletWorldImporter.h>
#include <string>

class CMeshCollider : public IComponent, public MeshColliderHelper {
    public:
        CMeshCollider(const std::string &BulletFile, float x, float y, float z);

        void setToKinematic();
        void setToStatic();

        CMeshCollider(const CMeshCollider &orig) = delete;
        ~CMeshCollider();

    private:
        btDefaultMotionState       myMotionState;

};

#endif
