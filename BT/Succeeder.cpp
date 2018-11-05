
#include <iostream>

#include "Succeeder.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//

Status Succeeder::update(){
  m_pChild->tick();
  if(m_pChild->getStatus()==BH_RUNNING){
    return BH_RUNNING;
  }else{
    return BH_SUCCESS;
  }
}
