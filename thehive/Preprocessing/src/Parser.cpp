#include "NavmeshParser.hpp"
#include "ModelParser.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {


    ModelParser::generateBinaryGG_Model("../assets/NavMeshes/Aux2_Exported_NavMeshFlipped.obj", "NavmeshCITY.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/SURREAL_TESTS/Cube.obj",                 "Cube.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/Basura_Cajas.obj",               "Basura_Cajas.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/ContenedorEnLaMenteDePablo.obj", "ContenedorEnLaMenteDePablo.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/Farola.obj",                     "Farola.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/InicioSuelo.obj",                "InicioSuelo.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/InicioCasa.obj",                 "InicioCasa.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/Nave.obj",                       "Nave.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/TuboRoto.obj",                   "TuboRoto.modelgg");

    ModelParser::generateBinaryGG_Model("../assets/NavMeshes/TEST.obj",                     "TEST.modelgg");

    ModelParser::generateBinaryGG_Model("../assets/Models/WEAPONS/pistola.obj",             "pistola.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Models/WEAPONS/escopeta.obj",             "escopeta.modelgg");


    for(uint16_t i = 1; i < 146; ++i)
        ModelParser::generateBinaryGG_Model("../assets/Models/INT8_T/"+std::to_string(i)+".obj",            std::to_string(i)+".modelgg");

    ModelParser::generateBinaryGG_Model("../assets/Models/Hero.obj",                        "Hero.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Models/SOLDIER.obj",                     "SOLDIER.modelgg");

    NavmeshParser::generateBinaryGG_Navmesh("../assets/NavMeshes/THE_HIVE.obj",             "NavmeshCITY.gg");

    return 0;
}
