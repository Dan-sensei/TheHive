#ifndef ZMESH_H
#define ZMESH_H

#include <vector>
#include <cstdint>
#include <Omicron/ZMaterial.hpp>
#include <Omicron/ZMESHES/ZMeshData.hpp>
#include <Omicron/CORE/TEntidad.hpp>
#include <glm/glm.hpp>
#include "BoundingBox.hpp"

class ZMesh : public TEntidad {
    friend class Omicron;
    public:
        void assignMaterial(ZMaterial* material_);

    protected:
        bool LODTest(const glm::vec3 Position, uint8_t &LOD);

        glm::mat4 MVP;

        static glm::vec3* CameraPosition;
        std::vector<ZMeshData*> MeshLODs;

        ZMaterial* zmat;
        uint16_t Radius;
};

#endif
