#include <iostream>
#include "Inverso.hpp"

Inverso::Inverso(Behavior* _m_pChild):Decorator(_m_pChild){}
Inverso::Inverso(){}
Inverso::~Inverso(){}

Status Inverso::update(){
  m_pChild->tick();
  if(m_pChild->getStatus()==BH_FAILURE)return BH_SUCCESS;
  if(m_pChild->getStatus()==BH_SUCCESS)return BH_FAILURE;
  //if(m_pChild->getStatus() == BH_RUNNING)return update();
  return m_pChild->getStatus();
}
void Inverso::onTerminate(Status state){
}
