#include <iostream>
#include "UntilFail.hpp"

Status UntilFail::update(){
  while(true){
    m_pChild->tick();
     if(m_pChild->getStatus()==BH_FAILURE){
      return BH_SUCCESS;
    }
    if(m_pChild->getStatus()==BH_INVALID){
      break;
    }
  }
  return BH_INVALID;
}
