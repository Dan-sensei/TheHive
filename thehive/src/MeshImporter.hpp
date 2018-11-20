#ifndef MESHIMPORTER_H
#define MESHIMPORTER_H

#include <vector>
#include <string>
#include <cstdint>
#include <GameAI/NavmeshStructs.hpp>
#include <iostream>

template <typename T>
class Singleton;

struct Edge{
    Edge();
    Edge(uint16_t _e1, uint16_t _e2);
    Edge(const Edge &orig);
    uint16_t e1 = 0;
    uint16_t e2 = 0;
    uint16_t face1 = 0;
    uint16_t face2 = 0;
    uint16_t ID = 0;
    bool operator==(const Edge &orig);
};

std::ostream& operator<<(std::ostream& os, const Edge &E);

class MeshImporter{
    friend class Singleton<MeshImporter>;
    public:

        bool importNavmesh(
            const std::string& pFile,
            std::vector<Node> &GRAPH,
            std::vector<std::vector<Connection>> &Connections
        );

        bool importNavmeshV2(
            const std::string& pFile,
            std::vector<Node> &GRAPH,
            std::vector<std::vector<Connection>> &Connections
        );

    private:
        MeshImporter();
        MeshImporter(const MeshImporter& orig) = delete;
        void operator=(MeshImporter const& orig) = delete;

};

#endif
