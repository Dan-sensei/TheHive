

#include "Selector.hpp"


 void Selector::onInitialize() {
  m_CurrentChild=m_Children.begin();
}

 Status Selector::update() {
  while (true) {
    Status s=(*m_CurrentChild)->tick();
    if(s != BH_FAILURE){
      if(s == BH_RUNNING)continue;
      return s;}
    if(++m_CurrentChild==m_Children.end()) return BH_FAILURE;
  }
  return BH_INVALID;
}
