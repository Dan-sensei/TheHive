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

    float minX, minY, minZ, maxX, maxY, maxZ;
    minX = minY = minZ = maxX = maxY = maxZ = 0;

    std::cout << "Hacking " << FileInput << " --> " << FileOutput << '\n';

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


        if(meshes[i]->mNumVertices > 0){
            minX = maxX = vertices[0].x;
            minY = maxY = vertices[0].y;
            minZ = maxZ = vertices[0].z;
        }

        for(uint16_t j = 0; j < meshes[i]->mNumVertices; ++j){

            if(vertices[j].x < minX) minX = vertices[j].x;
            if(vertices[j].x > maxX) maxX = vertices[j].x;

            if(vertices[j].y < minY) minY = vertices[j].y;
            if(vertices[j].y > maxY) maxY = vertices[j].y;

            if(vertices[j].z < minZ) minZ = vertices[j].z;
            if(vertices[j].z > maxZ) maxZ = vertices[j].z;

            PositionsNormals.emplace_back(vertices[j].x);
            PositionsNormals.emplace_back(vertices[j].y);
            PositionsNormals.emplace_back(vertices[j].z);

            PositionsNormals.emplace_back(normales[j].x);
            PositionsNormals.emplace_back(normales[j].y);
            PositionsNormals.emplace_back(normales[j].z);

            uv.emplace_back(textureCoords[j].x);
            uv.emplace_back(textureCoords[j].y);

            TangentsBitangents.emplace_back(tangents[j].x);
            TangentsBitangents.emplace_back(tangents[j].y);
            TangentsBitangents.emplace_back(tangents[j].z);

            TangentsBitangents.emplace_back(bitangents[j].x);
            TangentsBitangents.emplace_back(bitangents[j].y);
            TangentsBitangents.emplace_back(bitangents[j].z);
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


    std::ofstream BB(BB_BINARYFILES_OUTPUT_DIR+FileOutput+".bb", std::ios::binary);

    // MIN
    GG_Write(BB, minX);
    GG_Write(BB, minY);
    GG_Write(BB, minZ);      // .

    //Derecha
    GG_Write(BB, maxX);
    GG_Write(BB, minY);
    GG_Write(BB, minZ);      // . _____

    //Arriba
    GG_Write(BB, maxX);      //       .
    GG_Write(BB, maxY);      //       |
    GG_Write(BB, minZ);      // ._____|

    //Izquierda
    GG_Write(BB, minX);      // ._____.
    GG_Write(BB, maxY);      //       |
    GG_Write(BB, minZ);      // ._____|

    //-----------------------
    //Al fondo
    GG_Write(BB, minX);      // ./_____.
    GG_Write(BB, maxY);      //       |
    GG_Write(BB, maxZ);      // ._____|

    //Derecha
    GG_Write(BB, maxX);      //./====:
    GG_Write(BB, maxY);      //      |
    GG_Write(BB, maxZ);      //._____|

    //Abajo
    GG_Write(BB, maxX);
    GG_Write(BB, minY);
    GG_Write(BB, maxZ);

    //Izquierda
    GG_Write(BB, minX);
    GG_Write(BB, minY);
    GG_Write(BB, maxZ);
}
