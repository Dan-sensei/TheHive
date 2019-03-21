#include "NavmeshParser.hpp"
#include "ModelParser.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
    NavmeshParser::generateBinaryGG_Navmesh("../assets/Models/CIUDAD/Presentacion1/NAVMESH.obj", "NavmeshCITY.gg");



    ModelParser::generateBinaryGG_StaticModel("../assets/SURREAL_TESTS/Cube.obj",                 "Cube.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Objects/Basura_Cajas.obj",               "Basura_Cajas.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Objects/ContenedorEnLaMenteDePablo.obj", "ContenedorEnLaMenteDePablo.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Objects/Farola.obj",                     "Farola.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Objects/InicioSuelo.obj",                "InicioSuelo.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Objects/InicioCasa.obj",                 "InicioCasa.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Objects/Nave.obj",                       "Nave.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Objects/TuboRoto.obj",                   "TuboRoto.modelgg");

    ModelParser::generateBinaryGG_StaticModel("../assets/NavMeshes/TEST.obj",                        "TEST.modelgg");
    
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov0.obj",                        "SoldierMov0.modelgg");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov1.obj",                        "SoldierMov1.modelgg");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov2.obj",                        "SoldierMov2.modelgg");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov3.obj",                        "SoldierMov3.modelgg");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov4.obj",                        "SoldierMov4.modelgg");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov5.obj",                        "SoldierMov5.modelgg");

    for(uint16_t i = 1; i < 144; ++i)
        ModelParser::generateBinaryGG_StaticModel("../assets/Models/INT8_T/"+std::to_string(i)+".obj",            std::to_string(i)+".modelgg");

    ModelParser::generateBinaryGG_StaticModel("../assets/Models/Hero.obj",                         "Hero.modelgg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/SOLDIER.obj",                     "SOLDIER.modelgg");

    return 0;
}
