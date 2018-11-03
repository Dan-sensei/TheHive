#include <iostream>
#include "Singleton.hpp"
#include "Game.hpp"
#include "Util.hpp"

int main(int argc, char const *argv[]) {

    Game THE_HIVE;

    THE_HIVE.RUN();
    THE_HIVE.CLIN();

    return 0;
}
