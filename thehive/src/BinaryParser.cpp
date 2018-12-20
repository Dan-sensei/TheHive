#include "BinaryParser.hpp"
#include <fstream>

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
