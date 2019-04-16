#ifndef ZMESH_H
#define ZMESH_H

#include <vector>
#include <cstdint>
#include <Omicron/ZMaterial.hpp>
#include <Omicron/ZMESHES/ZMeshData.hpp>
#include <Omicron/CORE/TNodo.hpp>
#include <glm/glm.hpp>
#include "BoundingBox.hpp"

class ZMesh : public TEntidad {

    public:

        void assignMaterial(ZMaterial* material_);
        void loadBoundingBox(const std::string& BoundingBoxPath);

        static void setPlayerPtr(glm::vec3* _PlayerPosition);
        static void setCameraPtr(glm::vec3* _PlayerPosition);

    protected:
        void FrustrumTest(const glm::vec3 &Position, bool &dib);
        bool LODTest(const glm::vec3 Position, uint8_t &LOD);

        BoundingBox VOX;

        static glm::vec3* PlayerPosition;
        static glm::vec3* CameraPosition;
        std::vector<ZMeshData*> MeshLODs;

        ZMaterial* zmat;
        uint16_t Radius;
};

#endif
