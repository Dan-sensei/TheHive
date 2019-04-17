//#include <iostream>
#include "Repetidor.hpp"

Repetidor::Repetidor(Behavior* _m_pChild,float cont):Decorator(_m_pChild){
   contador=0;
   contador_max=cont;
}

void Repetidor::onInitialize(){
    contador=0;
}

Status Repetidor::update(){
  while(contador!=contador_max){
    m_pChild->tick();

     if(m_pChild->getStatus()==BH_FAILURE){
      return BH_FAILURE;
    }
    else if(m_pChild->getStatus()==BH_RUNNING){
      continue;
    }
    contador++;
  }
  return BH_SUCCESS;
}
