#ifndef BINARY_PARSER_H
#define BINARY_PARSER_H

#include <string>

class BinaryParser{
    public:
        ~BinaryParser();

        static void WriteNavmeshData(const std::string &file);

    private:
        BinaryParser() = delete;
        BinaryParser(const BinaryParser &orig) = delete;


};

#endif
