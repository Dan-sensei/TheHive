#include "NavmeshParser.hpp"
#include "ModelParser.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
    NavmeshParser::generateBinaryGG_Navmesh("../assets/Models/CIUDAD/Presentacion1/NAVMESH.obj", "NavmeshCITY.gg");
    ModelParser::generateBinaryGG_Model("../assets/SURREAL_TESTS/Cube.obj", "Cube.modelgg");
    return 0;
}
