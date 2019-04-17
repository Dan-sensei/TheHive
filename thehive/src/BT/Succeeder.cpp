//#include <iostream>
#include "Succeeder.hpp"

Status Succeeder::update(){
  m_pChild->tick();
  if(m_pChild->getStatus()==BH_FAILURE){
    return BH_SUCCESS;
  }else {
    //if(m_pChild->getStatus()==BH_RUNNING) return update();
    return m_pChild->getStatus();
  }
}
