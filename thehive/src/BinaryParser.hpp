#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

#include <string>
#include <GameAI/NavmeshStructs.hpp>
#include "Factory.hpp"
#include "Singleton.hpp"
#include "EventSystem/CTriggerSystem.hpp"
#include "EventSystem/TData.hpp"
#include "GameAI/AIDirector.hpp"
#include "SurrealEngine/NatureGenerator.hpp"

class BinaryParser{
    public:
        ~BinaryParser();

        static void ReadNavmeshData(
            const std::string &BinaryFile,
            std::vector<Node> &GRAPH,
            std::vector<std::vector<Connection>> &Connections,
            std::vector<Face> &SQUARE_FACES
        );

        static bool ImportMesh(
            const std::string& BinaryFile,
            std::vector<float> &PositionsNormals,
            std::vector<float> &uv,
            std::vector<float> &TangentsBitangents,
            std::vector<unsigned short> &index,
            std::array<float, 24>& BoudingBoxVertices,
            std::array<unsigned short, 36>& BoundingBox_IBO
        );

        static void ReadEventsData(const std::string &BinaryFile);
        static void ReadNatureData(const std::string &BinaryFile);

        static void ReadLoadZonesData(const std::string &BinaryFile);
        static void ReadUnLoadZonesData(const std::string &BinaryFile);
        static uint16_t ReadRespawnNodesData(const std::string &BinaryFile);

        static void LoadLevelData(const std::string &DARTA, int8_t map_zone = 0);

    private:
        BinaryParser() = delete;
        BinaryParser(const BinaryParser &orig) = delete;


};

#endif
