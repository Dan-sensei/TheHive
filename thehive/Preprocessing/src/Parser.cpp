#include "NavmeshParser.hpp"
#include "ModelParser.hpp"
//#include <iostream>

int main(int argc, char const *argv[]) {


    ModelParser::generateBinaryGG_StaticModel("../assets/NavMeshes/FINALNAV.obj",   "NavmeshCITY");
    ModelParser::generateBinaryGG_StaticModel("../assets/NavMeshes/TEST.obj",                           "TEST");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/WEAPONS/pistola.obj",                   "pistola");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/WEAPONS/escopeta.obj",                  "escopeta");
    ModelParser::generateBinaryGG_StaticModel("../assets/Models/fusible.obj",                           "fusible");

    for(uint16_t i = 1; i < 151; ++i){
        if (i == 70){
            ModelParser::generateBinaryGG_DynamicModel("../assets/Models/INT8_T/"+std::to_string(i)+".obj",           std::to_string(i));
        }
        else
            ModelParser::generateBinaryGG_StaticModel("../assets/Models/INT8_T/"+std::to_string(i)+".obj",            std::to_string(i));
    }

    ModelParser::generateBinaryGG_StaticModel("../assets/Models/HEROE/HERO_LOWLOWPOLY_FINAL.obj",                       "Hero");
    ModelParser::generateBinaryGG_StaticModel("../assets/NavMeshes/TEST.obj",                                           "TEST.modelgg");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/TANK/Attacking1_NT.obj",                        "Tank_Attacking1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/TANK/Attacking2_NT.obj",                        "Tank_Attacking2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/TANK/Attacking3_NT.obj",                        "Tank_Attacking3");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/TANK/Attacking4_NT.obj",                        "Tank_Attacking4");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/TANK/Walking1_NT.obj",                             "Tank_Walking1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/TANK/Walking2_NT.obj",                             "Tank_Walking2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/TANK/Walking3_NT.obj",                             "Tank_Walking3");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/Attacking1_NT.obj",                        "Soldier_Attacking1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/Attacking2_NT.obj",                        "Soldier_Attacking2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/Attacking3_NT.obj",                        "Soldier_Attacking3");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/Attacking4_NT.obj",                        "Soldier_Attacking4");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/Walking1_NT.obj",                          "Soldier_Walking1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/Walking2_NT.obj",                          "Soldier_Walking2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/Walking3_NT.obj",                          "Soldier_Walking3");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/DAMAGE_1.obj",                          "DAMAGE_1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/DAMAGE_2.obj",                          "DAMAGE_2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/SOLDIER/DAMAGE_3.obj",                          "DAMAGE_3");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking1.obj",                                "Walking1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking2.obj",                                "Walking2");

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking_Weapon1.obj",                        "Walking_Weapon1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/Walking_Weapon2.obj",                        "Walking_Weapon2");

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

    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/WAVE_1.obj",                        "WAVE_1");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/WAVE_2.obj",                        "WAVE_2");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/WAVE_3.obj",                        "WAVE_3");
    ModelParser::generateBinaryGG_DynamicModel("../assets/Animations/HERO/WAVE_4.obj",                        "WAVE_4");

    // ModelParser::generateBinaryGG_StaticModel("../assets/Models/nature_test1.obj",                "nature_test1");
    // ModelParser::generateBinaryGG_StaticModel("../assets/Models/flor.obj",                        "flor");
    // ModelParser::generateBinaryGG_StaticModel("../assets/Models/nature1.obj",                     "nature1");
    //
    // ModelParser::generateBinaryGG_StaticModel("../assets/Models/arbol.obj",                     "arbol");

    NavmeshParser::generateBinaryGG_Navmesh("../assets/NavMeshes/FINALNAV.obj",             "NavmeshCITY.nav");
    NavmeshParser::generateBinaryGG_NavmeshZone("../assets/NavMeshes/ZONA_1.obj",             "ZONA_1.nav_z");
    NavmeshParser::generateBinaryGG_NavmeshZone("../assets/NavMeshes/ZONA_2.obj",             "ZONA_2.nav_z");
    NavmeshParser::generateBinaryGG_NavmeshZone("../assets/NavMeshes/ZONA_3.obj",             "ZONA_3.nav_z");
    NavmeshParser::generateBinaryGG_NavmeshZone("../assets/NavMeshes/ZONA_4.obj",             "ZONA_4.nav_z");
    NavmeshParser::generateBinaryGG_NavmeshZone("../assets/NavMeshes/ZONA_5.obj",             "ZONA_5.nav_z");
    NavmeshParser::generateBinaryGG_NavmeshZone("../assets/NavMeshes/ZONA_6.obj",             "ZONA_6.nav_z");
    NavmeshParser::generateBinaryGG_NavmeshZone("../assets/NavMeshes/ZONA_7.obj",             "ZONA_7.nav_z");

    return 0;
}
