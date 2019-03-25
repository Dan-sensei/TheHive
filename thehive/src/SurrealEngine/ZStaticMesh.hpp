#ifndef ZSTATICMESH_H
#define ZSTATICMESH_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "ZMeshData.hpp"
#include "TNodo.hpp"
#include <glm/glm.hpp>
#include "BoundingBox.hpp"

class ZStaticMesh : public TEntidad {
    public:
        ZStaticMesh();
        ZStaticMesh(const ZStaticMesh &orig) = delete;
        ~ZStaticMesh();

        bool load(const std::string& Name);
        void loadBoundingBox(const std::string& BoundingBoxPath);
        void assignMaterial(ZMaterial* material_);
        void beginDrawwithoutligt();

        virtual void beginDraw();
        virtual void endDraw();

        void addLOD(std::string Name);

        static void setPlayerPtr(glm::vec3* _PlayerPosition);
        static void setCameraPtr(glm::vec3* _PlayerPosition);

    private:

        BoundingBox VOX;

        static glm::vec3* PlayerPosition;
        static glm::vec3* CameraPosition;
        std::vector<ZMeshData*> MeshLODs;

        ZMaterial* zmat;
};

#endif
