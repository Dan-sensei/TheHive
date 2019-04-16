#ifndef ZMOVABLEMESH_H
#define ZMOVABLEMESH_H

#include <Omicron/CORE/TNodo.hpp>
#include <glm/glm.hpp>
#include "ZMesh.hpp"

class ZMovableMesh : public ZMesh {
    public:
        ZMovableMesh();
        ZMovableMesh(const ZMovableMesh &orig) = delete;
        ~ZMovableMesh();

        bool load(const std::string& Name);

        virtual void beginDraw();
        virtual void endDraw();
};

#endif
