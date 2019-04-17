#ifndef ZSTATICMESH_H
#define ZSTATICMESH_H

#include <Omicron/CORE/TNodo.hpp>
#include <glm/glm.hpp>
#include "ZMesh.hpp"

class ZStaticMesh : public ZMesh {
    public:
        ZStaticMesh(const glm::mat4 TheModelMatrix);
        ZStaticMesh(const ZStaticMesh &orig) = delete;
        ~ZStaticMesh();

        bool load(const std::string& Name);
        void beginDrawwithoutligt();

        virtual void beginDraw();
        virtual void endDraw();

        void addLOD(std::string Name);

    private:

        glm::mat4 localModelMatrix;
};

#endif
