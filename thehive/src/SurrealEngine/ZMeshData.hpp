#ifndef ZMESHDATA_H
#define ZMESHDATA_H

#include <vector>
#include <cstdint>
#include <string>
#include "ZMaterial.hpp"

struct ZMeshData{

        ZMeshData();
        ZMeshData(const ZMeshData &orig);
        ~ZMeshData();

        bool load(const std::string& path);

        std::vector< float > Positions;
        std::vector< float > UV_Coords;
        std::vector< float > Normals;
        std::vector< float > Tangents;
        std::vector< float > Bitangents;
        std::vector< unsigned short > Indexes;

        ZMaterial* zmat;
};

#endif