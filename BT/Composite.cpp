#include "Composite.hpp"


void Composite::addChild(Behavior* hijo){
  m_Children.push_back(hijo);
}

void Composite::removeChild(Behavior* hijo){
  Behaviors::iterator m_CurrentChild;
  m_CurrentChild=m_Children.begin();
  while(m_CurrentChild!=m_Children.end()){
    if(*m_CurrentChild==hijo){
      m_Children.erase(m_CurrentChild);
      break;
    }
    m_CurrentChild++;
  }
}

void Composite::clearChildren(){
    m_Children.clear();
}
