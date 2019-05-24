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

void ModelParser::generateBinaryGG_StaticModel(const std::string &FileInput, const std::string& FileOutput){
    parser(FileInput, FileOutput, 0);
}

void ModelParser::generateBinaryGG_DynamicModel(const std::string &FileInput, const std::string& FileOutput){
    parser(FileInput, FileOutput, 1);
}

void ModelParser::parser(const std::string &FileInput, const std::string& FileOutput, unsigned int dyn){
    std::vector<float> THE_BUFFER;
    std::vector<unsigned short> index;

    Assimp::Importer importer;

    const aiScene* scene;

    if(dyn){
        scene = importer.ReadFile(
            FileInput,
            aiProcess_Triangulate            |
            aiProcess_CalcTangentSpace       |
            aiProcess_FlipUVs                |
            aiProcess_SortByPType
        );
    }
    else{
        scene = importer.ReadFile(
            FileInput,
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_CalcTangentSpace       |
            aiProcess_FlipUVs                |
            aiProcess_SortByPType
        );
    }


    // If the import failed, report it
    if( !scene){
        std::cout << "La importación de " << FileInput << " ha fallado" << '\n';
        return;
    }

    std::cout << "Hacking " << FileInput << " --> " << FileOutput << '\n';

    aiMesh **meshes = scene->mMeshes;
    aiVector3D* vertices;
    aiVector3D* textureCoords;
    aiVector3D* normales;
    aiVector3D* tangents;
    aiVector3D* bitangents;
    aiFace* faces;

    if(scene->mNumMeshes > 0 && meshes[0]->mNumVertices > 0){
        vertices   =   meshes[0]->mVertices;
    }

    for(uint16_t i = 0; i < scene->mNumMeshes; ++i){

             vertices   =   meshes[i]->mVertices;
        textureCoords   =   meshes[i]->mTextureCoords[0];
             normales   =   meshes[i]->mNormals;
             tangents   =   meshes[i]->mTangents;
           bitangents   =   meshes[i]->mBitangents;
                faces   =   meshes[i]->mFaces;

            THE_BUFFER.reserve(meshes[i]->mNumVertices*6 + meshes[i]->mNumVertices*2 + meshes[i]->mNumVertices*3);


        for(uint16_t j = 0; j < meshes[i]->mNumVertices; ++j){

            THE_BUFFER.emplace_back(vertices[j].x);
            THE_BUFFER.emplace_back(vertices[j].y);
            THE_BUFFER.emplace_back(vertices[j].z);

            THE_BUFFER.emplace_back(normales[j].x);
            THE_BUFFER.emplace_back(normales[j].y);
            THE_BUFFER.emplace_back(normales[j].z);

            THE_BUFFER.emplace_back(textureCoords[j].x);
            THE_BUFFER.emplace_back(textureCoords[j].y);

            THE_BUFFER.emplace_back(tangents[j].x);
            THE_BUFFER.emplace_back(tangents[j].y);
            THE_BUFFER.emplace_back(tangents[j].z);

            // TangentsBitangents.emplace_back(bitangents[j].x);
            // TangentsBitangents.emplace_back(bitangents[j].y);
            // TangentsBitangents.emplace_back(bitangents[j].z);
        }

        index.reserve(meshes[i]->mNumFaces*3);
        for(uint16_t j = 0; j < meshes[i]->mNumFaces; ++j){
            const aiFace& Face = faces[j];
            assert(Face.mNumIndices == 3);
            index.emplace_back(Face.mIndices[0]);
            index.emplace_back(Face.mIndices[1]);
            index.emplace_back(Face.mIndices[2]);
        }
    }

    std::ofstream MODEL(MODELS_BINARYFILES_OUTPUT_DIR+FileOutput+".modelgg", std::ios::binary);

    uint16_t POSITIONS_AND_NORMALS_SIZE = THE_BUFFER.size();
    GG_Write(MODEL, POSITIONS_AND_NORMALS_SIZE);
    for(uint16_t i = 0; i < POSITIONS_AND_NORMALS_SIZE; ++i){
        GG_Write(MODEL, THE_BUFFER[i]);
    }
    //
    // uint16_t UV_COORDS_SIZE = uv.size();
    // GG_Write(MODEL, UV_COORDS_SIZE);
    // for(uint16_t i = 0; i < UV_COORDS_SIZE; ++i){
    //     GG_Write(MODEL, uv[i]);
    // }
    //
    // uint16_t TANGENTS_AND_BITANGENTS_SIZE = TangentsBitangents.size();
    // GG_Write(MODEL, TANGENTS_AND_BITANGENTS_SIZE);
    // for(uint16_t i = 0; i < TANGENTS_AND_BITANGENTS_SIZE; ++i){
    //     GG_Write(MODEL, TangentsBitangents[i]);
    // }
    //
    uint16_t INDEX_SIZE = index.size();
    GG_Write(MODEL, INDEX_SIZE);
    for(uint16_t i = 0; i < INDEX_SIZE; ++i){
        GG_Write(MODEL, index[i]);
    }
}
