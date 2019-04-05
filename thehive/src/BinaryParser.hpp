#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

#include <string>
#include <GameAI/NavmeshStructs.hpp>
#include "Factory.hpp"
#include "Singleton.hpp"
#include "EventSystem/CTriggerSystem.hpp"
#include "EventSystem/TData.hpp"
#include "GameAI/AIDirector.hpp"
#include "Omicron/NatureGenerator.hpp"
#include <Omicron/ZMESHES/BoundingBox.hpp>
#include "Util.hpp"

namespace BinaryParser{
    void ReadNavmeshData(
        const std::string &BinaryFile,
        std::vector<Node> &GRAPH,
        std::vector<std::vector<Connection>> &Connections,
        std::vector<Face> &SQUARE_FACES
    );

    bool ImportMesh(
        const std::string& BinaryFile,
        std::vector<float> &PositionsNormals,
        std::vector<float> &uv,
        std::vector<float> &TangentsBitangents,
        std::vector<unsigned short> &index
    );

    bool ReadBoundingBox(const std::string &BinaryFile, BoundingBox* THE_BOX);

    void ReadNatureData(const std::string &BinaryFile);

    void ReadLoadZonesData(const std::string &BinaryFile);
    void ReadUnLoadZonesData(const std::string &BinaryFile);
    uint16_t ReadRespawnNodesData(const std::string &BinaryFile);

    void LoadLevelData(const std::string &DARTA, int8_t map_zone = 0);
};

#endif
