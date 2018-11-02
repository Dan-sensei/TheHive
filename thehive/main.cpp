#include <iostream>
#include <cstdint>
#include <iomanip>
#include <map>
#include <string>

#include "Singleton.hpp"
#include "Arena.hpp"

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

class Dummy{
    public:
        Dummy(uint16_t _u, uint8_t _x, uint8_t _y)
        :uee(_u), x(_x), y(_y)
        {
            std::cout << "Construyendo Dummy \n";
        };
        ~Dummy(){
            std::cout << "Destruyendo Dummy \n";
        };
    private:
        uint16_t uee;
        uint8_t x, y;
};


void *operator new(std::size_t size, Arena &A){
    return A.allocate(size);
}

void operator delete(void* p, Arena &A){
    return A.deallocate(p);
}

int main(int argc, char const *argv[]) {

    std::cout << "Ey yo wassup my nigga" << std::endl;
    uint8_t* p;

    Arena DummyArena(128);

    std::map<uint16_t, Dummy*>  OBJ;

    OBJ[0] = new (DummyArena) Dummy(1, 2, 3);
    OBJ[1] = new (DummyArena) Dummy(3, 4, 5);
    OBJ[3] = new (DummyArena) Dummy(6, 7, 8);

    // Print memory
    p  = reinterpret_cast<uint8_t*>(OBJ[0]) - 16;
    printRawMem(p, 16, 10);
    std::cout << "--------------\n";

    OBJ[0]->~Dummy();
    DummyArena.deallocate(OBJ[0]);

    OBJ[1]->~Dummy();
    DummyArena.deallocate(OBJ[1]);

    OBJ[3]->~Dummy();
    DummyArena.deallocate(OBJ[2]);


    return 0;
}
