#ifndef NavmeshParser_H
#define NavmeshParser_H

#include <vector>
#include <string>
#include <cstdint>
//#include <iostream>

template <typename T>
class Singleton;

struct Edge{
    Edge();
    Edge(uint16_t _vertex1, uint16_t _vertex2);
    Edge(const Edge &orig);
    uint16_t vertex1 = 0;
    uint16_t vertex2 = 0;
    uint16_t face = 0;
    uint16_t ID = 0;
};

std::ostream& operator<<(std::ostream& os, const Edge &E);

namespace NavmeshParser{
    void generateBinaryGG_Navmesh(const std::string& _File, const std::string &FileName);
    void generateBinaryGG_NavmeshZone(const std::string& _File, const std::string &FileName);
};

#endif
