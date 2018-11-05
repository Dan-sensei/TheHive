
#include <iostream>

#include "inverso.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//

Status inverso::update(){
  m_pChild->tick();
  if(m_pChild->getStatus()==BH_FAILURE){
    return BH_SUCCESS;
  }
  if(m_pChild->getStatus()==BH_SUCCESS){
    return BH_FAILURE;
  }
  return BH_RUNNING;
}
