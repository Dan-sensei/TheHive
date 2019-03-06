#include "NavmeshParser.hpp"
#include "ModelParser.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
    NavmeshParser::generateBinaryGG_Navmesh("../assets/Models/CIUDAD/Presentacion1/NAVMESH.obj", "NavmeshCITY.gg");



    ModelParser::generateBinaryGG_Model("../assets/SURREAL_TESTS/Cube.obj",                 "Cube.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/Basura_Cajas.obj",               "Basura_Cajas.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/ContenedorEnLaMenteDePablo.obj", "ContenedorEnLaMenteDePablo.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/Farola.obj",                     "Farola.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/InicioSuelo.obj",                "InicioSuelo.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/InicioCasa.obj",                 "InicioCasa.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/Nave.obj",                       "Nave.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/TuboRoto.obj",                   "TuboRoto.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Objects/SQUARE.obj",                     "SQUARE.modelgg");

    ModelParser::generateBinaryGG_Model("../assets/Models/CALLE_PRINCIPAL/5.obj",            "5.modelgg");

    for(uint16_t i = 30; i < 93; ++i)
        ModelParser::generateBinaryGG_Model("../assets/Models/CALLE_PRINCIPAL/"+std::to_string(i)+".obj",            std::to_string(i)+".modelgg");

    for(uint16_t i = 130; i < 138; ++i)
        ModelParser::generateBinaryGG_Model("../assets/Models/CALLE_PRINCIPAL/"+std::to_string(i)+".obj",            std::to_string(i)+".modelgg");

    ModelParser::generateBinaryGG_Model("../assets/Models/Hero.obj",                         "Hero.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Models/SOLDIER.obj",                     "SOLDIER.modelgg");

    return 0;
}
