#include <iostream>
#include "Singleton.hpp"
//#include <irrlicht/irrlicht.h>

#include "Game.hpp"
int main(int argc, char const *argv[]) {

    Game THE_HIVE;

    THE_HIVE.RUN();
    THE_HIVE.CLIN();

    return 0;
}
