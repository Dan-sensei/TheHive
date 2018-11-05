
#include <iostream>

#include "UntilFail.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//

Status UntilFail::update(){
  while(true){
    m_pChild->tick();
    if(m_pChild->getStatus()==BH_SUCCESS || m_pChild->getStatus()==BH_RUNNING){
      break;
    }else if(m_pChild->getStatus()==BH_FAILURE){
      return BH_SUCCESS;
    }

  }
  return BH_RUNNING;

}
