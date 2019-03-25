#include "NavmeshParser.hpp"
#include "ModelParser.hpp"
//#include <iostream>

int main(int argc, char const *argv[]) {


    ModelParser::generateBinaryGG_Model("../assets/NavMeshes/Aux2_Exported_NavMeshFlipped.obj", "NavmeshCITY");
    ModelParser::generateBinaryGG_Model("../assets/NavMeshes/TEST.obj",                        "TEST");
    ModelParser::generateBinaryGG_Model("../assets/Models/WEAPONS/pistola.obj",             "pistola");
    ModelParser::generateBinaryGG_Model("../assets/Models/WEAPONS/escopeta.obj",             "escopeta");

    for(uint16_t i = 1; i < 146; ++i)
        ModelParser::generateBinaryGG_Model("../assets/Models/INT8_T/"+std::to_string(i)+".obj",            std::to_string(i));

    ModelParser::generateBinaryGG_Model("../assets/Models/HEROE/HERO_LOWLOWPOLY_FINAL.obj",                         "Hero");
    ModelParser::generateBinaryGG_Model("../assets/NavMeshes/TEST.obj",                        "TEST.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Animations/SoldierMov/SoldierMov0.obj",                        "SoldierMov0.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Animations/SoldierMov/SoldierMov1.obj",                        "SoldierMov1.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Animations/SoldierMov/SoldierMov2.obj",                        "SoldierMov2.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Animations/SoldierMov/SoldierMov3.obj",                        "SoldierMov3.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Animations/SoldierMov/SoldierMov4.obj",                        "SoldierMov4.modelgg");
    ModelParser::generateBinaryGG_Model("../assets/Animations/SoldierMov/SoldierMov5.obj",                        "SoldierMov5.modelgg");

    NavmeshParser::generateBinaryGG_Navmesh("../assets/NavMeshes/THE_HIVE.obj",             "NavmeshCITY.gg");
    ModelParser::generateBinaryGG_Model("../assets/Models/nature_test1.obj",                "nature_test1");
    ModelParser::generateBinaryGG_Model("../assets/Models/flor.obj",                        "flor");
    ModelParser::generateBinaryGG_Model("../assets/Models/nature1.obj",                     "nature1");

    return 0;
}
