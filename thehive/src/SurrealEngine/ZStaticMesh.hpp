#ifndef ZSTATICMESH_H
#define ZSTATICMESH_H

#include <vector>
#include <cstdint>
#include "ZMaterial.hpp"
#include "ZMeshData.hpp"
#include "TNodo.hpp"

class ZStaticMesh : public TEntidad {
    public:
        ZStaticMesh();
        ZStaticMesh(const ZStaticMesh &orig) = delete;
        ~ZStaticMesh();

        bool load(const std::string& Name);
        void assignMaterial(ZMaterial* material_);
        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

    private:

        ZMeshData* mesh;
        ZMaterial* zmat;
};

#endif
