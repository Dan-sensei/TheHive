#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

#include <string>
#include <GameAI/NavmeshStructs.hpp>

class BinaryParser{
    public:
        ~BinaryParser();

        static void ReadNavmeshData(
            const std::string &_File,
            std::vector<Node> &GRAPH,
            std::vector<std::vector<Connection>> &Connections,
            std::vector<Face> &SQUARE_FACES
        );

        static bool ImportMesh(
            const std::string& pFile,
            std::vector<float> &PositionsNormals,
            std::vector<float> &uv,
            std::vector<float> &TangentsBitangents,
            std::vector<unsigned short> &index
        );

        static void test();

    private:
        BinaryParser() = delete;
        BinaryParser(const BinaryParser &orig) = delete;


};

#endif
