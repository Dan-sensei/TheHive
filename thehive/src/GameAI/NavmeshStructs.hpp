#ifndef NAVMESHSTRUCTS_H
#define NAVMESHSTRUCTS_H

#include <cstdint>
#include <string>
#include <iostream>

enum Type{
    OPEN = 0,
    CLOSED,
    UNVISITED
};

struct Connection{
    Connection(uint16_t _From = 0, uint16_t _To = 0, float _Value = 0, std::string _Name = "None");
    Connection(const Connection &orig);

    uint16_t From;
    uint16_t To;
    float Value;
    std::string Name;
};

struct Node{
    Node();
    Node(uint16_t _ID, float _X, float _Y, float _Z);
    Node(const Node &orig);

    uint16_t ID;
    Connection Bitconnect;
    float RealCost;
    float Heuristic;
    float EstimatedCost;
    float X, Y, Z;
    Type Status;
};

std::ostream& operator<<(std::ostream& os, const Node &N);

#endif
