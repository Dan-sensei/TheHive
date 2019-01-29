#include "BinaryParser.hpp"
#include <fstream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <cassert>

template<typename T>
std::istream & GG_Read(std::istream& _istream, T& value){
    return _istream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void BinaryParser::ReadNavmeshData(
    const std::string &_File,
    std::vector<Node> &GRAPH,
    std::vector<std::vector<Connection>> &Connections,
    std::vector<Face> &SQUARE_FACES
){

    std::ifstream inStream(_File, std::ios::binary);

    uint16_t GRAPH_SIZE;
    GG_Read(inStream, GRAPH_SIZE);
    for(uint16_t i = 0; i < GRAPH_SIZE; ++i){

        uint16_t ID;
        GG_Read(inStream, ID);

        uint16_t NODE_1;
        GG_Read(inStream, NODE_1);

        uint16_t NODE_2;
        GG_Read(inStream, NODE_2);

        gg::Vector3f Position;
        GG_Read(inStream, Position);

        float Radius;
        GG_Read(inStream, Radius);

        GRAPH.emplace_back(ID, NODE_1, NODE_2, Position, Radius);
    }

    uint16_t CONNECTIONS_SIZE;
    GG_Read(inStream, CONNECTIONS_SIZE);
    Connections.resize(CONNECTIONS_SIZE);

    for(uint16_t i = 0; i < CONNECTIONS_SIZE; ++i){
        uint16_t CONNECTION_X_SIZE;
        GG_Read(inStream, CONNECTION_X_SIZE);
        for(uint16_t j = 0; j < CONNECTION_X_SIZE; ++j){
            float Value;
            GG_Read(inStream, Value);

            uint16_t From;
            GG_Read(inStream, From);

            uint16_t To;
            GG_Read(inStream, To);

            Connections[i].emplace_back(Value, From, To);
        }
    }

    uint16_t SQUARE_FACES_SIZE;
    GG_Read(inStream, SQUARE_FACES_SIZE);
    for(uint16_t i = 0; i < SQUARE_FACES_SIZE; ++i){
        gg::Vector3f TL;
        GG_Read(inStream, TL);

        gg::Vector3f BR;
        GG_Read(inStream, BR);

        SQUARE_FACES.emplace_back(TL, BR);

        uint16_t PORTALS_SIZE;
        GG_Read(inStream, PORTALS_SIZE);
        for(uint16_t j = 0; j < PORTALS_SIZE; ++j){
            uint16_t PortalID;
            GG_Read(inStream, PortalID);
            SQUARE_FACES.back().Portals.push_back(PortalID);
        }

    }

}


bool BinaryParser::ImportMesh(
    const std::string& pFile,
    std::vector<float> &vertex,
    std::vector<float> &uv,
    std::vector<float> &normal,
    std::vector<float> &tangent,
    std::vector<float> &bitangent,
    std::vector<unsigned short> &index
){

    vertex.clear();
    uv.clear();
    normal.clear();
    index.clear();
    // Create an instance of the Importer class
    Assimp::Importer importer;
    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // propably to request more postprocessing than we do in this example.
    const aiScene* scene = importer.ReadFile( pFile,
    aiProcess_CalcTangentSpace       |
    aiProcess_Triangulate            |
    aiProcess_JoinIdenticalVertices  |
    aiProcess_SortByPType);


    // If the import failed, report it
    if( !scene)
        return false;

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

        for(uint16_t j = 0; j < meshes[i]->mNumVertices; ++j){
            vertex.push_back(vertices[j].x);
            vertex.push_back(vertices[j].y);
            vertex.push_back(vertices[j].z);

            uv.push_back(textureCoords[j].x);
            uv.push_back(textureCoords[j].y);

            normal.push_back(normales[j].x);
            normal.push_back(normales[j].y);
            normal.push_back(normales[j].z);

            tangent.push_back(tangents[j].x);
            tangent.push_back(tangents[j].y);
            tangent.push_back(tangents[j].z);

            bitangent.push_back(bitangents[j].x);
            bitangent.push_back(bitangents[j].y);
            bitangent.push_back(bitangents[j].z);
        }


        for(uint16_t j = 0; j < meshes[i]->mNumFaces; ++j){
            const aiFace& Face = faces[j];
            assert(Face.mNumIndices == 3);
            index.push_back(Face.mIndices[0]);
            index.push_back(Face.mIndices[1]);
            index.push_back(Face.mIndices[2]);
        }

        // std::cout << "   |-- VERTICES: " << meshes[0]->mNumVertices << '\n';
        // std::cout << "   |-- INDICES:  " << index.size() << '\n';
    }

    return true;
}