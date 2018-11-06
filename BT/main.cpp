#include <iostream>

#include "behaviorTree.hpp"
#include "Filter.hpp"
#include "hoja.hpp"
#include "hoja0.hpp"

#include "inverso.hpp"//si
#include "Repetidor.hpp"
#include "Selector.hpp"
#include "sequence.hpp"//si
#include "Succeeder.hpp"
#include "UntilFail.hpp"

#include "ActiveSelector.hpp"//important
#include "Monitor.hpp"//important

#include "Parallel.hpp"





int main() {


hoja* hoja1=new hoja();
hoja* hoja2=new hoja();
hoja* hoja3=new hoja();
hoja0* hoja4=new hoja0();



inverso* inv1 = new inverso(hoja3);


sequence*  sec1=new sequence();

sec1->addChild(hoja1);
sec1->addChild(hoja4);
sec1->addChild(hoja2);
sec1->addChild(inv1);



BehaviorTree BT(sec1);

std::cout << "tick 1" << '\n';
BT.tick();
std::cout << "tick 2" << '\n';
BT.tick();
std::cout << "tick 3" << '\n';
BT.tick();
std::cout << "tick 4" << '\n';
BT.tick();

delete sec1;
delete hoja1;
delete hoja2;
delete hoja3;
delete hoja4;
delete inv1;



   // Ejemplo con decorator
   /*
   bhprueba* bh1     = new bhprueba();
   decorator* dec    = new decorator(bh1);

   dec->update();
   dec->update();
   dec->update();
   dec->update();

   dec->update();
   // */
   return 0;
}
