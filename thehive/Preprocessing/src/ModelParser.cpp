#include "ModelParser.hpp"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <cassert>

#include "BinaryHelper.hpp"
#include <fstream>

#include <vector>
#include <iostream>

#include "FILE_DIRECTORIES.hpp"


ModelParser::ModelParser(){}

void ModelParser::generateBinaryGG_Model(const std::string &FileInput, const std::string& FileOutput){
    std::vector<float> PositionsNormals;
    std::vector<float> uv;
    std::vector<float> TangentsBitangents;
    std::vector<unsigned short> index;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        FileInput,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_FlipUVs                |
        aiProcess_SortByPType
    );


    // If the import failed, report it
    if( !scene){
        std::cout << "La importación de " << FileInput << " ha fallado" << '\n';
        return;
    }


    std::cout << "Loading " << FileInput << "..." << '\n';
    //std::cout << "Cargando modelo '" << pFile << "'" << '\n';

    aiMesh **meshes = scene->mMeshes;
    aiVector3D* vertices;
    aiVector3D* textureCoords;
    aiVector3D* normales;
    aiVector3D* tangents;
    aiVector3D* bitangents;
    aiFace* faces;

    for(uint16_t i = 0; i < scene->mNumMeshes; ++i){

             vertices   =   meshes[i]->mVertices;
        textureCoords   =   meshes[i]->mTextureCoords[0];
             normales   =   meshes[i]->mNormals;
             tangents   =   meshes[i]->mTangents;
           bitangents   =   meshes[i]->mBitangents;
                faces   =   meshes[i]->mFaces;

            PositionsNormals.reserve(meshes[i]->mNumVertices*6);
            uv.reserve(meshes[i]->mNumVertices*2);
            TangentsBitangents.reserve(meshes[i]->mNumVertices*6);

        for(uint16_t j = 0; j < meshes[i]->mNumVertices; ++j){
            PositionsNormals.push_back(vertices[j].x);
            PositionsNormals.push_back(vertices[j].y);
            PositionsNormals.push_back(vertices[j].z);

            PositionsNormals.push_back(normales[j].x);
            PositionsNormals.push_back(normales[j].y);
            PositionsNormals.push_back(normales[j].z);

            uv.push_back(textureCoords[j].x);
            uv.push_back(textureCoords[j].y);

            TangentsBitangents.push_back(tangents[j].x);
            TangentsBitangents.push_back(tangents[j].y);
            TangentsBitangents.push_back(tangents[j].z);

            TangentsBitangents.push_back(bitangents[j].x);
            TangentsBitangents.push_back(bitangents[j].y);
            TangentsBitangents.push_back(bitangents[j].z);
        }

        index.reserve(meshes[i]->mNumFaces*3);
        for(uint16_t j = 0; j < meshes[i]->mNumFaces; ++j){
            const aiFace& Face = faces[j];
            assert(Face.mNumIndices == 3);
            index.push_back(Face.mIndices[0]);
            index.push_back(Face.mIndices[1]);
            index.push_back(Face.mIndices[2]);
        }
    }

    std::ofstream MODEL(MODELS_BINARYFILES_OUTPUT_DIR+FileOutput, std::ios::binary);

    uint16_t POSITIONS_AND_NORMALS_SIZE = PositionsNormals.size();
    GG_Write(MODEL, POSITIONS_AND_NORMALS_SIZE);
    for(uint16_t i = 0; i < POSITIONS_AND_NORMALS_SIZE; ++i){
        GG_Write(MODEL, PositionsNormals[i]);
    }

    uint16_t UV_COORDS_SIZE = uv.size();
    GG_Write(MODEL, UV_COORDS_SIZE);
    for(uint16_t i = 0; i < UV_COORDS_SIZE; ++i){
        GG_Write(MODEL, uv[i]);
    }

    uint16_t TANGENTS_AND_BITANGENTS_SIZE = TangentsBitangents.size();
    GG_Write(MODEL, TANGENTS_AND_BITANGENTS_SIZE);
    for(uint16_t i = 0; i < TANGENTS_AND_BITANGENTS_SIZE; ++i){
        GG_Write(MODEL, TangentsBitangents[i]);
    }

    uint16_t INDEX_SIZE = index.size();
    GG_Write(MODEL, INDEX_SIZE);
    for(uint16_t i = 0; i < INDEX_SIZE; ++i){
        GG_Write(MODEL, index[i]);
    }


}
