#include "MeshImporter.hpp"
#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <Util.hpp>
#include <cmath>
#include <list>
MeshImporter::MeshImporter(){

}


// bool MeshImporter::importNavmesh(
//     const std::string& pFile,
//     std::vector<Node> &GRAPH,
//     std::vector<std::vector<Connection>> &Connections
// ){
//
//     std::vector<gg::Vector3f> vertex;
//     std::vector<uint16_t> index;
//     std::vector<Edge> Edges;
//
//     Assimp::Importer importer;
//
//     const aiScene* scene = importer.ReadFile( pFile,
//     aiProcess_JoinIdenticalVertices  |
//     aiProcess_SortByPType);
//
//
//     if( !scene)
//         return false;
//
//     std::cout << "Loading model '" << pFile << "'" << '\n';
//
//     aiMesh **meshes = scene->mMeshes;
//     aiVector3D* vertices;
//     aiFace* faces;
//
//     vertices   =   meshes[0]->mVertices;
//        faces   =   meshes[0]->mFaces;
//
//
//     std::vector<Edge> v;
//
//     for(uint16_t j = 0; j < meshes[0]->mNumVertices; ++j){
//         vertex.emplace_back(vertices[j].x, vertices[j].y, vertices[j].z);
//     }
//
//     std::cout << "mNumFaces " << meshes[0]->mNumFaces << '\n';
//
//     Connections.resize(meshes[0]->mNumFaces);
//
//     for(uint16_t j = 0; j < meshes[0]->mNumFaces; ++j) {
//
//         const aiFace& Face = faces[j];
//
//         float X = 0;
//         float Y = 0;
//         float Z = 0;
//
//         for(uint8_t i = 0; i < Face.mNumIndices; ++i){
//             X += vertex[Face.mIndices[i]].X;
//             Y += vertex[Face.mIndices[i]].Y;
//             Z += vertex[Face.mIndices[i]].Z;
//             index.push_back(Face.mIndices[i]);
//
//             //Edge NewEdge(Face.mIndices[i], Face.mIndices[(i+1)%Face.mNumIndices], j);
//
//             uint16_t it = 0;
//             bool found = false;
//             while(it < Edges.size()) {
//
//                 //if(NewEdge == Edges[it]) {
//                 //    //Connections[j].emplace_back(j, Edges[it].face, 0, "[" + std::to_string(j) + "-" + std::to_string(Edges[it].face) + "]");
//                 //    //Connections[Edges[it].face].emplace_back(Edges[it].face, j, 0, "[" + std::to_string(Edges[it].face) + "-" + std::to_string(j) + "]");
//                 //    found = true;
//                 //    break;
//                 //}
//                 ++it;
//
//             }
//
//             //if (!found)
//             //    Edges.push_back(NewEdge);
//         }
//
//         GRAPH.emplace_back(j, gg::Vector3f(-X/Face.mNumIndices, Y/Face.mNumIndices, Z/Face.mNumIndices));
//     }
//
//     if(false) {
//         std::cout << '\n' << "VERTEX: " << '\n';
//         for(int i = 0; i < vertex.size(); ++i)
//             std::cout << " " << i << " -> ("<< vertex[i].X << ", " << vertex[i].Y << ", " << vertex[i].Z  <<")" << '\n';
//
//         std::cout << '\n';
//
//         std::cout << "INDEXES: " << '\n';
//         for(int i = 0; i < index.size(); ++i)
//             std::cout << " " << index[i];
//
//         std::cout << '\n' << '\n';
//
//         std::cout << "EDGES: " << '\n';
//         for(int i = 0; i < Edges.size(); ++i)
//             std::cout << " " << Edges[i] << '\n';
//
//         std::cout << '\n' << '\n';
//
//         std::cout << "   |-- VERTEX : " << meshes[0]->mNumVertices << '\n';
//         std::cout << "   |--  INDEX : " << index.size() << '\n' << '\n';
//     }
//
//     return true;
// }

bool MeshImporter::importNavmeshV2(
    const std::string& pFile,
    std::vector<Node> &GRAPH,
    std::vector<std::vector<Connection>> &Connections,
    std::vector<Face> &SQUARE_FACES
){

    std::vector<gg::Vector3f> vertex;
    std::list<Edge> Edges;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile( pFile,0);


    if( !scene)
        return false;

    //std::cout << "Loading model '" << pFile << "'" << '\n';

    aiMesh **meshes = scene->mMeshes;
    aiVector3D* vertices;
    aiFace* faces;

    vertices   =   meshes[0]->mVertices;
       faces   =   meshes[0]->mFaces;

    for(uint16_t j = 0; j < meshes[0]->mNumVertices; ++j){
        vertex.emplace_back(vertices[j].x*-1, vertices[j].y, vertices[j].z);
    }

    //std::cout << "mNumFaces " << meshes[0]->mNumFaces << '\n';

    Connections.resize(meshes[0]->mNumFaces);

    uint16_t ID_Counter = 0;

    std::vector<std::vector<Edge>> FACES(meshes[0]->mNumFaces);

    for(uint16_t j = 0; j < meshes[0]->mNumFaces; ++j) {
        const aiFace& Face = faces[j];

        std::vector<gg::Vector3f> minX;
        std::vector<gg::Vector3f> maxX;

        for(uint16_t i = 0; i < Face.mNumIndices; ++i){
            if(!minX.empty() && minX.front().X - vertex[Face.mIndices[i]].X > 0.001) {
                minX.clear();
                minX.push_back(vertex[Face.mIndices[i]]);
            }
            else if(minX.empty() || abs(vertex[Face.mIndices[i]].X - minX.front().X) < 0.001) {
                minX.push_back(vertex[Face.mIndices[i]]);
            }

            if(!maxX.empty() && vertex[Face.mIndices[i]].X - maxX.front().X > 0.001) {
                maxX.clear();
                maxX.push_back(vertex[Face.mIndices[i]]);
            }
            else if(maxX.empty() || abs(vertex[Face.mIndices[i]].X - maxX.front().X) < 0.001) {
                maxX.push_back(vertex[Face.mIndices[i]]);
            }
        }

        gg::Vector3f TL = minX.front();
        gg::Vector3f BL = minX.front();
        for(uint16_t i = 1; i < minX.size(); ++i){
            if(minX[i].Z > TL.Z)
                TL = minX[i];

            if(minX[i].Z < BL.Z)
                BL = minX[i];
        }

        gg::Vector3f TR = maxX.front();
        gg::Vector3f BR = maxX.front();
        for(uint16_t i = 1; i < maxX.size(); ++i){
            if(maxX[i].Z > TR.Z)
                TR = maxX[i];

            if(maxX[i].Z < BR.Z)
                BR = maxX[i];
        }


        SQUARE_FACES.emplace_back(j,  TL, TR, BR, BL);

        for(uint16_t i = 0; i < Face.mNumIndices; ++i){
            Edge NewEdge(Face.mIndices[i], Face.mIndices[(i+1)%Face.mNumIndices]);
            NewEdge.face = j;

            auto it = Edges.begin();
            bool found = false;
            while(it != Edges.end()) {
                //std::cout << "FOUND!" << '\n';

                if(
                    (vertex[NewEdge.vertex1] == vertex [(*it).vertex1]    &&
                     vertex[NewEdge.vertex2] == vertex [(*it).vertex2])
                     ||
                    (vertex[NewEdge.vertex1] == vertex [(*it).vertex2]    &&
                     vertex[NewEdge.vertex2] == vertex [(*it).vertex1])
                ) {
                    (*it).ID = ID_Counter;
                    FACES[j].push_back(*it);
                    FACES[(*it).face].push_back(*it);

                    gg::Vector3f NodeCoords = gg::Vector3f((vertex[(*it).vertex1] + vertex[(*it).vertex2])/2);
                    GRAPH.emplace_back(ID_Counter, j, (*it).face, NodeCoords, gg::DIST(NodeCoords, vertex[(*it).vertex1]));
                    found = true;
                    ++ID_Counter;
                    Edges.erase(it);
                    break;
                }
                ++it;

            }

            if (!found)
                Edges.push_back(NewEdge);
        }
    }

    Connections.resize(ID_Counter);
    for(uint16_t i = 0; i < FACES.size(); ++i) {
        if(FACES[i].size() > 1){
            for(uint16_t j = 0; j < FACES[i].size(); ++j) {
                SQUARE_FACES[i].Portals.push_back(FACES[i][j].ID);
                for(uint16_t k = 0; k < FACES[i].size(); ++k) {
                    if(FACES[i][j].ID != FACES[i][k].ID)
                        Connections[FACES[i][j].ID].emplace_back(0, FACES[i][j].ID, FACES[i][k].ID/*, vertex[FACES[i][j].vertex1], vertex[FACES[i][j].vertex2]*/);
                }
            }
        }
    }

    //if(true) {
        //std::cout << '\n' << "VERTEX: " << '\n';
        //for(int i = 0; i < vertex.size(); ++i)
            //std::cout << " " << i << " -> ("<< vertex[i].X << ", " << vertex[i].Y << ", " << vertex[i].Z  <<")" << '\n';

        //std::cout << '\n';

        //std::cout << "INDEXES: " << '\n';
        //for(int i = 0; i < index.size(); ++i)
            //std::cout << " " << index[i];

        //std::cout << '\n' << '\n';

        //std::cout << "EDGES: " << '\n';
        //for(int i = 0; i < Edges.size(); ++i)
        //    std::cout << " " << Edges[i] << '\n';

        //std::cout << '\n' << '\n';

        //std::cout << "   |-- VERTEX : " << meshes[0]->mNumVertices << '\n';
        //std::cout << "   |--  INDEX : " << index.size() << '\n' << '\n';
    //}

    return true;
}


Edge::Edge()
:vertex1(0), vertex2(0), face(0), ID(0)
{}

Edge::Edge(const Edge &orig){
    vertex1 = orig.vertex1;
    vertex2 = orig.vertex2;
    face = orig.face;
    ID = orig.ID;
}

Edge::Edge(uint16_t _vertex1, uint16_t _vertex2)
:vertex1(_vertex1), vertex2(_vertex2), ID(0)
{}


std::ostream& operator<<(std::ostream& os, const Edge &E){
    os << "[" << E.vertex1 << "," << E.vertex2 << "]";
    return os;
}
