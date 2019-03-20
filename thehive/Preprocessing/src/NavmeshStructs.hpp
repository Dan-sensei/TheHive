#ifndef NAVMESHSTRUCTS_H
#define NAVMESHSTRUCTS_H

#include <cstdint>
#include <string>
//#include <iostream>
#include <vector>
#include "Util.hpp"

enum Type{
    OPEN = 0,
    CLOSED,
    UNVISITED
};

struct Face{
    Face(const glm::vec3 _TL, const glm::vec3 _BR);
    Face(const Face &orig);

    std::vector<uint16_t> Portals;
    glm::vec3 TL, BR;
};

struct Connection{
    Connection(float _Value = 0, uint16_t _From = 0, uint16_t _To = 0/*, const glm::vec3 &_Vertex1 = glm::vec3(), const glm::vec3 &_Vertex2 = glm::vec3()*/);
    Connection(const Connection &orig);

    //glm::vec3 Vertex1;
    //glm::vec3 Vertex2;
    float Value;
    uint16_t From;
    uint16_t To;
};

struct Node{
    Node();
    Node(uint16_t _ID, uint16_t _NODE_1, uint16_t _NODE_2, const glm::vec3 &_Position, float _Radius);
    Node(const Node &orig);

    glm::vec3 Position;
    Connection Bitconnect;
    float RealCost;
    float EstimatedCost;
    float Radius;
    Type Status;
    uint16_t ID;
    uint16_t NODE_1;
    uint16_t NODE_2;
};

struct Waypoint{
    Waypoint();
    Waypoint(const glm::vec3 &_Position, uint16_t _ID, float _Radius);
    Waypoint(const Waypoint &orig);

    glm::vec3 Position;
    float Radius;
    uint16_t ID;
};


#endif
