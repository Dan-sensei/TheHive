#ifndef _CMESHCOLLIDER_H
#define _CMESHCOLLIDER_H

#include <ComponentArch/IComponent.hpp>
#include "Collider.hpp"
#include <BulletWorldImporter/btBulletWorldImporter.h>
#include <string>

class CMeshCollider : public IComponent, public Collider {
    public:
        CMeshCollider(const std::string &BulletFile, float x, float y, float z);

        void setToKinematic();
        void setToStatic();

        CMeshCollider(const CMeshCollider &orig) = delete;
        ~CMeshCollider();

    private:
        btBulletWorldImporter*      fileLoader;
};

#endif
