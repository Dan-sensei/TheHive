#include <iostream>

#include "BehaviorTree.hpp"
#include "Andar_rand.hpp"
#include "Comer.hpp"
#include "Girar.hpp"
#include "Mover.hpp"
#include "Rango_visual.hpp"
#include "RandomSelector.hpp"
#include "Repetidor.hpp"
#include "Selector.hpp"
#include "Sequence.hpp"


int main() {

    Andar_rand andar_r= Andar_rand();
    Rango_visual rango= Rango_visual();
    Girar giro= Girar();
    Mover move_to= Mover();
    Comer com= Comer();




    Sequence sec1= Sequence();
    Sequence  sec2= Sequence();

    sec2.addChild(&rango);
    sec2.addChild(&giro);

    sec1.addChild(&sec2);
    sec1.addChild(&move_to);
    sec1.addChild(&com);

    RandomSelector selec1=  RandomSelector();
    selec1.addChild(&andar_r);
    selec1.addChild(&sec1);

    BehaviorTree BT(&selec1);

    std::cout << "tick 1" << '\n';
    BT.tick();


    return 0;
}
