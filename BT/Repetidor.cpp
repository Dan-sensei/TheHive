
#include <iostream>

#include "Repetidor.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//
Repetidor::Repetidor(behavior* _m_pChild,float cont):decorator(_m_pChild)
{
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
