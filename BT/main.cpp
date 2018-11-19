#include <iostream>

#include "BehaviorTree.hpp"
#include "RandomSelector.hpp"
#include "RandomSequence.hpp"
#include "Action.hpp"


int main() {

    Action andar_r= Action(ANDAR_RAND);
    Action rango= Action(RANGO);
    Action giro= Action(GIRAR);
    Action move_to= Action(MOVER);
    Action com= Action(COMER);

    RandomSequence sec1= RandomSequence();
    sec1.addChild(&rango);
    sec1.addChild(&giro);

    RandomSequence  sec2= RandomSequence();
    sec2.addChild(&sec1);
    sec2.addChild(&move_to);
    sec2.addChild(&com);

    RandomSelector selec1=  RandomSelector();
    selec1.addChild(&andar_r);
    selec1.addChild(&sec2);

    BehaviorTree BT(&selec1);

    BT.tick();


    return 0;
}
