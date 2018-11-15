#include <iostream>

#include "BehaviorTree.hpp"
#include "Filter.hpp"
#include "Andar_rand.hpp"
#include "Comer.hpp"
#include "Girar.hpp"
#include "Mover.hpp"
#include "Rango_visual.hpp"
#include "Inverso.hpp"
#include "Repetidor.hpp"
#include "Selector.hpp"
#include "Sequence.hpp"
#include "Succeeder.hpp"
#include "UntilFail.hpp"
#include "ActiveSelector.hpp"
#include "Monitor.hpp"
#include "Parallel.hpp"

int main() {

    Andar_rand* andar_r=new Andar_rand();
    Rango_visual* rango=new Rango_visual();
    Girar* giro=new Girar();
    Mover* move_to=new Mover();
    Comer* com=new Comer();


    Sequence*  sec1=new Sequence();
    Sequence*  sec2=new Sequence();

    sec2->addChild(rango);
    sec2->addChild(giro);

    sec1->addChild(sec2);
    sec1->addChild(move_to);
    sec1->addChild(com);

    Selector* selec1= new Selector();
    selec1->addChild(andar_r);
    selec1->addChild(sec1);

    BehaviorTree BT(selec1);

    std::cout << "tick 1" << '\n';
    BT.tick();

    delete sec1;
    delete sec2;
    delete selec1;
    delete com;
    delete move_to;
    delete giro;
    delete rango;
    delete andar_r;

    return 0;
}
