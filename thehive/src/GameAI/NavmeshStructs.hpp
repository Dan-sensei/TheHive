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
    Connection(uint16_t _From = 0, uint16_t _To = 0, float _Value = 0, const gg::Vector3f &_Vertex1 = gg::Vector3f(), const gg::Vector3f &_Vertex2 = gg::Vector3f());
    Connection(const Connection &orig);

    gg::Vector3f Vertex1;
    gg::Vector3f Vertex2;
    float Value;
    uint16_t From;
    uint16_t To;
};

struct Node{
    Node();
    Node(uint16_t _ID, const gg::Vector3f &_Position, float _Radius);
    Node(const Node &orig);

    Connection Bitconnect;
    gg::Vector3f Position;
    float RealCost;
    float Heuristic;
    float EstimatedCost;
    float Radius;
    Type Status;
    uint16_t ID;
};

struct Waypoint{
    Waypoint();
    Waypoint(const gg::Vector3f &_Position, uint16_t _ID, float _Radius);
    Waypoint(const Waypoint &orig);

    gg::Vector3f Position;
    float Radius;
    uint16_t ID;
};

std::ostream& operator<<(std::ostream& os, const Node &N);

#endif
