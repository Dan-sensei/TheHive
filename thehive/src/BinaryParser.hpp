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

    private:
        BinaryParser() = delete;
        BinaryParser(const BinaryParser &orig) = delete;


};

#endif
