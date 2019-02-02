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

        std::vector< float > PositionsNormals;
        std::vector< float > UV_Coords;
        std::vector< float > TangentsBitangents;
        std::vector< unsigned short > Indexes;

        ZMaterial* zmat;
};

#endif