#ifndef NAVMESHSTRUCTS_H
#define NAVMESHSTRUCTS_H

#include <cstdint>
#include <string>
#include <iostream>
#include <Util.hpp>

enum Type{
    OPEN = 0,
    CLOSED,
    UNVISITED
};


struct Connection{
    Connection(uint16_t _From = 0, uint16_t _To = 0, float _Value = 0, std::string _Name = "None");
    Connection(const Connection &orig);

    std::string Name;
    float Value;
    uint16_t From;
    uint16_t To;
};

struct Node{
    Node();
    Node(uint16_t _ID, const gg::Vector3f &_Position);
    Node(const Node &orig);

    Connection Bitconnect;
    gg::Vector3f Position;
    float RealCost;
    float Heuristic;
    float EstimatedCost;
    Type Status;
    uint16_t ID;
};

struct Waypoint{
    Waypoint();
    Waypoint(const gg::Vector3f &_Position, uint16_t _ID);
    Waypoint(const Waypoint &orig);

    gg::Vector3f Position;
    uint16_t ID;
};

std::ostream& operator<<(std::ostream& os, const Node &N);

#endif
