#include "NavmeshParser.hpp"
#include <iostream>
#include <fstream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <cmath>
#include <list>

#include "NavmeshStructs.hpp"
#include "Util.hpp"
#include "BinaryHelper.hpp"

NavmeshParser::NavmeshParser(){}

void NavmeshParser::generateBinaryGG_Navmesh(const std::string& _File) {
    std::ofstream CITY("../assets/BinaryFiles/NavmeshCITY.gg", std::ios::binary);

    std::vector<Node> GRAPH;
    std::vector<std::vector<Connection>> Connections;
    std::vector<Face> SQUARE_FACES;

    std::vector<gg::Vector3f> vertex;
    std::list<Edge> Edges;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile( "../"+_File,0);


    if( !scene){
        std::cout << "Couldn't open file" << '\n';
        return;
    }

    std::cout << "Loading model '" << _File << "'" << '\n';

    aiMesh **meshes = scene->mMeshes;
    aiVector3D* vertices;
    aiFace* faces;

    vertices   =   meshes[0]->mVertices;
       faces   =   meshes[0]->mFaces;

    for(uint16_t j = 0; j < meshes[0]->mNumVertices; ++j){
        vertex.emplace_back(vertices[j].x*-1, vertices[j].y, vertices[j].z);
    }

    // std::cout << "mNumFaces " << meshes[0]->mNumFaces << '\n';

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
        }

        gg::Vector3f TR = maxX.front();
        gg::Vector3f BR = maxX.front();
        for(uint16_t i = 1; i < maxX.size(); ++i){
            if(maxX[i].Z < BR.Z)
                BR = maxX[i];
        }

        SQUARE_FACES.emplace_back(TL, BR);

        for(uint16_t i = 0; i < Face.mNumIndices; ++i){
            Edge NewEdge(Face.mIndices[i], Face.mIndices[(i+1)%Face.mNumIndices]);
            NewEdge.face = j;

            auto it = Edges.begin();
            bool found = false;
            while(it != Edges.end()) {
                //// std::cout << "FOUND!" << '\n';

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

            if (!found) Edges.push_back(NewEdge);
        }
    }
    // std::cout << "CONNECTIONS SIZE " << ID_Counter << '\n';
    Connections.resize(ID_Counter);
    for(uint16_t i = 0; i < FACES.size(); ++i) {
        for(uint16_t j = 0; j < FACES[i].size(); ++j) {
            SQUARE_FACES[i].Portals.push_back(FACES[i][j].ID);
            for(uint16_t k = 0; k < FACES[i].size(); ++k) {
                if(FACES[i][j].ID != FACES[i][k].ID)
                    Connections[FACES[i][j].ID].emplace_back(0, FACES[i][j].ID, FACES[i][k].ID);
            }
        }
    }

    for(uint16_t i = 0; i < Connections.size(); ++i){
        for(uint16_t j = 0; j < Connections[i].size(); ++j){
            if(Connections[i][j].Value == 0)
                Connections[i][j].Value = gg::DIST(GRAPH[Connections[i][j].From].Position, GRAPH[Connections[i][j].To].Position);
        }
    }


    std::cout << "SQUARE_FACES -> " << SQUARE_FACES.size() << '\n';

    uint16_t GRAPH_SIZE = GRAPH.size();
    GG_Write(CITY, GRAPH_SIZE);
    for(auto i : GRAPH){
        GG_Write(CITY, i.ID);
        GG_Write(CITY, i.NODE_1);
        GG_Write(CITY, i.NODE_2);
        GG_Write(CITY, i.Position);
        GG_Write(CITY, i.Radius);
    }

    uint16_t CONNECTIONS_SIZE = Connections.size();
    GG_Write(CITY, CONNECTIONS_SIZE);
    for(auto i : Connections){
        uint16_t CONNECTION_X_SIZE = i.size();
        GG_Write(CITY, CONNECTION_X_SIZE);
        for(auto j : i) {
            float Value = j.Value;
            GG_Write(CITY, Value);

            uint16_t From = j.From;
            GG_Write(CITY, From);

            uint16_t To = j.To;
            GG_Write(CITY, To);
        }
    }

    uint16_t SQUARE_FACES_SIZE = SQUARE_FACES.size();
    GG_Write(CITY, SQUARE_FACES_SIZE);
    for(auto i : SQUARE_FACES){
        uint16_t PORTALS_SIZE = i.Portals.size();
        GG_Write(CITY, PORTALS_SIZE);
        for(auto j : i.Portals)
            GG_Write(CITY, j);

        GG_Write(CITY, i.TL);
        GG_Write(CITY, i.BR);
    }
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
