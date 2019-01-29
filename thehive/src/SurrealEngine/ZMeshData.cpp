#include "ZMeshData.hpp"
#include <GL/glew.h>
#include <BinaryParser.hpp>
#include "OpenGEnum.hpp"
#include "AssetManager.hpp"

ZMeshData::ZMeshData()
{
    zmat = AssetManager::getMaterial("Default");
}

ZMeshData::ZMeshData(const ZMeshData &orig){
    uint16_t i;

    Positions.resize(orig.Positions.size());
    for(uint16_t i = 0; i < Positions.size(); ++i){
        Positions[i] = orig.Positions[i];
    }

    UV_Coords.resize(orig.UV_Coords.size());
    for(uint16_t i = 0; i < UV_Coords.size(); ++i){
        UV_Coords[i] = orig.UV_Coords[i];
    }

    Normals.resize(orig.Normals.size());
    for(uint16_t i = 0; i < Normals.size(); ++i){
        Normals[i] = orig.Normals[i];
    }

    Tangents.resize(orig.Tangents.size());
    for(uint16_t i = 0; i < Tangents.size(); ++i){
        Tangents[i] = orig.Tangents[i];
    }

    Bitangents.resize(orig.Bitangents.size());
    for(uint16_t i = 0; i < Bitangents.size(); ++i){
        Bitangents[i] = orig.Bitangents[i];
    }

    Indexes.resize(orig.Indexes.size());
    for(uint16_t i = 0; i < Indexes.size(); ++i){
        Indexes[i] = orig.Indexes[i];
    }

    zmat = orig.zmat;
}

ZMeshData::~ZMeshData(){
    //std::cout << "Deleting mesh..." << '\n';
}

bool ZMeshData::load(const std::string& path){

    bool loaded = BinaryParser::ImportMesh(path, Positions, UV_Coords, Normals, Tangents, Bitangents, Indexes);
    if(!loaded){
        std::cout << "   --No se pudo abrir " << path << '\n';
        return false;
    }

    return true;
}