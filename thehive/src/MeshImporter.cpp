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
    std::vector<std::vector<Connection>> &Connections
){

    std::vector<gg::Vector3f> vertex;
    std::vector<uint16_t> index;
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
        vertex.emplace_back(vertices[j].x, vertices[j].y, vertices[j].z);
    }

    //std::cout << "mNumFaces " << meshes[0]->mNumFaces << '\n';

    Connections.resize(meshes[0]->mNumFaces);

    uint16_t ID_Counter = 0;

    std::vector<std::vector<Edge>> FACES;
    FACES.resize(meshes[0]->mNumFaces);

    //std::cout << "FACES SIZE = " << FACES.size() << '\n';
    for(uint16_t j = 0; j < meshes[0]->mNumFaces; ++j) {

        const aiFace& Face = faces[j];

        for(uint8_t i = 0; i < Face.mNumIndices; ++i){

            index.push_back(Face.mIndices[i]);

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
                    GRAPH.emplace_back(ID_Counter, NodeCoords * gg::Vector3f(-1,1,1), gg::DIST(NodeCoords, vertex[(*it).vertex1]));
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
    for(uint16_t i = 0; i < FACES.size(); ++i){
        if(FACES[i].size() > 1){
            for(uint16_t j = 0; j < FACES[i].size(); ++j){
                for(uint16_t k = 0; k < FACES[i].size(); ++k){
                    if(FACES[i][j].ID != FACES[i][k].ID)
                        Connections[FACES[i][j].ID].emplace_back(FACES[i][j].ID, FACES[i][k].ID, 0, vertex[FACES[i][j].vertex1], vertex[FACES[i][j].vertex2]);
                }
            }
        }
    }

    if(true) {
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
    }

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

bool Edge::operator==(const Edge &Edgvertex2){
    return ((vertex1 == Edgvertex2.vertex1 && vertex2 == Edgvertex2.vertex2) || (vertex1 == Edgvertex2.vertex2 && vertex2 == Edgvertex2.vertex1));
}

std::ostream& operator<<(std::ostream& os, const Edge &E){
    os << "[" << E.vertex1 << "," << E.vertex2 << "]";
    return os;
}
