#include <iostream>

#include "behaviorTree.hpp"
#include "Filter.hpp"
#include "hoja.hpp"
#include "hoja0.hpp"

#include "inverso.hpp"
#include "Repetidor.hpp"
#include "Selector.hpp"
#include "sequence.hpp"
#include "Succeeder.hpp"
#include "UntilFail.hpp"



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


BT.tick();


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
