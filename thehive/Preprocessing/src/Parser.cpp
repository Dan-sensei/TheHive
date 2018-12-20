#include "NavmeshParser.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
    NavmeshParser::generateBinaryGG_Navmesh("assets/NavMeshes/PROTOTIPO_CIUDAD.obj", "NavmeshCITY");
    NavmeshParser::generateBinaryGG_Navmesh("assets/NavMeshes/L4D2Nav.obj", "L4D2Nav");
    return 0;
}
