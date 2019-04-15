#include "NavmeshParser.hpp"
#include "ModelParser.hpp"
//#include <iostream>

int main(int argc, char const *argv[]) {


    ModelParser::generateBinaryGG_StaticModel("../assets/NavMeshes/Aux2_Exported_NavMeshFlipped.obj",   "NavmeshCITY");
    ModelParser::generateBinaryGG_StaticModel("../assets/NavMeshes/TEST.obj",                           "TEST");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/WEAPONS/pistola.obj",                   "pistola");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/WEAPONS/escopeta.obj",                  "escopeta");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/fusible.obj",                           "fusible");

    for(uint16_t i = 1; i < 147; ++i){
        if(i == 144)
            ModelParser::generateBinaryGG_StaticModel("../assets/Models/INT8_T/"+std::to_string(i)+".obj",            std::to_string(i), false);
        else if (i == 70)
            ModelParser::generateBinaryGG_DynamicModel("../assets/Models/INT8_T/"+std::to_string(i)+".obj",           std::to_string(i));
        else
            ModelParser::generateBinaryGG_StaticModel("../assets/Models/INT8_T/"+std::to_string(i)+".obj",            std::to_string(i));
    }

    ModelParser::generateBinaryGG_StaticModel("../assets/Models/HEROE/HERO_LOWLOWPOLY_FINAL.obj",                         "Hero");
    ModelParser::generateBinaryGG_StaticModel("../assets/NavMeshes/TEST.obj",                           "TEST.modelgg");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov0.obj",                        "SoldierMov0");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov1.obj",                        "SoldierMov1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov2.obj",                        "SoldierMov2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov3.obj",                        "SoldierMov3");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov4.obj",                        "SoldierMov4");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SoldierMov/SoldierMov5.obj",                        "SoldierMov5");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking1.obj",                        "Walking1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking2.obj",                        "Walking2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking3.obj",                        "Walking3");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking_Weapon1.obj",                        "Walking_Weapon1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking_Weapon2.obj",                        "Walking_Weapon2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking_Weapon3.obj",                        "Walking_Weapon3");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Standing1.obj",                        "Standing1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Standing2.obj",                        "Standing2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Standing3.obj",                        "Standing3");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping1.obj",                        "Jumping1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping2.obj",                        "Jumping2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping3.obj",                        "Jumping3");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping4.obj",                        "Jumping4");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping_Walking1.obj",                        "Jumping_Walking1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping_Walking2.obj",                        "Jumping_Walking2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping_Walking3.obj",                        "Jumping_Walking3");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Jumping_Walking4.obj",                        "Jumping_Walking4");

    NavmeshParser::generateBinaryGG_Navmesh("../assets/NavMeshes/THE_HIVE.obj",             "NavmeshCITY.gg");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/nature_test1.obj",                "nature_test1");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/flor.obj",                        "flor");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/nature1.obj",                     "nature1");

    ModelParser::generateBinaryGG_StaticModel("../assets/Models/arbol.obj",                     "arbol");

    return 0;
}
