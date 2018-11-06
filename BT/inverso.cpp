
#include <iostream>

#include "inverso.hpp"

// Rama del arbol con solo un hijo
// Los comportamientos del hijo pueden repetirse n veces si se quiere

//-----------------------------------------//
// Esta es la estructura de cada DECORATOR //
//-----------------------------------------//
inverso::inverso(behavior* _m_pChild)
:decorator(_m_pChild)
{}
inverso::inverso(){}
inverso::~inverso(){}


Status inverso::update(){
  std::cout << "inverso update" <<getStatus() << '\n';
  m_pChild->tick();
  if(m_pChild->getStatus()==BH_FAILURE)return BH_SUCCESS;
  if(m_pChild->getStatus()==BH_SUCCESS)return BH_FAILURE;
  //if(m_pChild->getStatus() == BH_RUNNING)return update();
  return m_pChild->getStatus();
}
void inverso::onTerminate(Status state){
  std::cout << "inverso onTerminate" <<state << '\n';

}
