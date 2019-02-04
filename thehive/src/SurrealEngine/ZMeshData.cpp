#include "ZMeshData.hpp"
#include <GL/glew.h>
#include "BinaryParser.hpp"
#include "OpenGEnum.hpp"
#include "AssetManager.hpp"
#include <iostream>

ZMeshData::ZMeshData()
{
    zmat = AssetManager::getMaterial("Default");
}

ZMeshData::ZMeshData(const ZMeshData &orig){
    uint16_t i;

    PositionsNormals.resize(orig.PositionsNormals.size());
    for(uint16_t i = 0; i < PositionsNormals.size(); ++i){
        PositionsNormals[i] = orig.PositionsNormals[i];
    }

    UV_Coords.resize(orig.UV_Coords.size());
    for(uint16_t i = 0; i < UV_Coords.size(); ++i){
        UV_Coords[i] = orig.UV_Coords[i];
    }

    TangentsBitangents.resize(orig.TangentsBitangents.size());
    for(uint16_t i = 0; i < TangentsBitangents.size(); ++i){
        TangentsBitangents[i] = orig.TangentsBitangents[i];
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

    bool loaded = BinaryParser::ImportMesh(path, PositionsNormals, UV_Coords, TangentsBitangents, Indexes);
    if(!loaded){
        std::cout << "   --No se pudo abrir " << path << '\n';
        return false;
    }

    return true;
}