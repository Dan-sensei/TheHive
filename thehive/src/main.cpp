
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
//            std::cout << "Construyendo Dummy \n";
//        };
//        ~Dummy(){
//            std::cout << "Destruyendo Dummy \n";
//        };
//    private:
//        uint16_t uee;
//        uint8_t x, y;
//};


//#include<>
int main(int argc, char const *argv[]) {
    //std::stack<Waypoint> WP;
    //Singleton<Pathfinding>::Instance()->A_Estrella2(0, 20, WP);
    //Singleton<Pathfinding>::Instance()->A_Estrella(0, 20, WP);



    //return 0;
    Game THE_HIVE;

    THE_HIVE.RUN();
    THE_HIVE.CLIN();

    return 0;
}
