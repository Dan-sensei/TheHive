#include <iostream>
#include <cstdint>
#include <iomanip>
#include <map>
#include <string>

#include "Singleton.hpp"
#include "Arena.hpp"
#include "ObjectManager.hpp"
#include "Game.hpp"
#include "Util.hpp"

//Funciones de Fran Gallego para imprimir memoria por consola ==============================¬
//                                                                                          |
//====================================================================================      |
// Pretty print a 2-digits hexadecimal value                                                |
//====================================================================================      |
void printHexVal(uint16_t val) {
   std::cout << std::hex << std::setw(2) << std::setfill('0') << val;
}

//====================================================================================
// Print a memory slice as raw bytes
//====================================================================================
void printRawMem(uint8_t* p, uint16_t linebytes, uint16_t lines) {
   for(uint16_t l=0; l < lines; ++l) {
      std::cout << reinterpret_cast<uint16_t*>(p) << " ";
      for(uint16_t u=0; u < linebytes; ++u) {
         printHexVal(*p);
         ++p;
         std::cout << " ";
      }
      std::cout << "\n";
   }
}
//============================================================================================

//class Dummy{
//    public:
//        Dummy(uint16_t _u, uint8_t _x, uint8_t _y)
//        :uee(_u), x(_x), y(_y)
//        {
//            std::cout << "Construyendo Dummy \n";
//        };
//        ~Dummy(){
//            std::cout << "Destruyendo Dummy \n";
//        };
//    private:
//        uint16_t uee;
//        uint8_t x, y;
//};




int main(int argc, char const *argv[]) {

    std::cout << "Init" << std::endl;
    Game THE_HIVE;

    THE_HIVE.RUN();
    THE_HIVE.CLIN();


    uint8_t* p;

    ObjectManager Manager;

    uint16_t hero = Manager.createEntity();
    std::cout << "Hero " << hero << std::endl;

    Manager.addComponentToEntity(TRANSFORM, hero);
    // Print memory
    //p  = reinterpret_cast<uint8_t*>(2) - 16;
    //printRawMem(p, 16, 10);
    //std::cout << "--------------\n";

    std::cout << "End" << std::endl;


    return 0;
}
