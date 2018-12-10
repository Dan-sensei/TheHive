
#include "Game.hpp"
#include <iostream>
#include <string>
#include <Singleton.hpp>
#include "GameAI/Pathfinding.hpp"
#include "GameAI/NavmeshStructs.hpp"

//class Dummy{
//    public:
//        Dummy(uint16_t _u, uint8_t _x, uint8_t _y)
//        :uee(_u), x(_x), y(_y)
//        {
//            // std::cout << "Construyendo Dummy \n";
//        };
//        ~Dummy(){
//            // std::cout << "Destruyendo Dummy \n";
//        };
//    private:
//        uint16_t uee;
//        uint8_t x, y;
//};


//#include<>
int main(int argc, char const *argv[]) {

    Game THE_HIVE;

    THE_HIVE.RUN();
    THE_HIVE.CLIN();

    return 0;
}
//[0-3]-[3-5]-[5-8]-[8-18]-[18-17]-[17-16]-[16-15]-[15-13]-[13-11]-[11-22]-[22-23]-[23-21]-[21-20]
//[0-3]-[3-5]-[5-4]-[4-9]-[9-19]-[19-20]
