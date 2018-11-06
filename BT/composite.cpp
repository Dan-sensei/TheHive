
#include "composite.hpp"
 void composite::addChild(behavior* hijo){
  m_Children.push_back(hijo);
}
 void composite::removeChild(behavior* hijo){
  behaviors::iterator m_CurrentChild;
  m_CurrentChild=m_Children.begin();
  while(m_CurrentChild!=m_Children.end()){
    if(*m_CurrentChild==hijo){
      m_Children.erase(m_CurrentChild);
      break;
    }
    m_CurrentChild++;
  }
}
 void composite::clearChildren(){
m_Children.clear();
}
