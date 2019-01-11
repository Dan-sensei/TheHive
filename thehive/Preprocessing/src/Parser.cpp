#include "NavmeshParser.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
    NavmeshParser::generateBinaryGG_Navmesh("assets/Models/CIUDAD/Presentacion1/NAVMESH.obj", "NavmeshCITY.gg");
    return 0;
}
