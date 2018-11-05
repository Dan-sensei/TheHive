

#include "sequence.hpp"


 void sequence::onInitialize() {
  m_CurrentChild=m_Children.begin();
}
/*
virtual Status update() override{
  while (true) {
    Status s=(*m_CurrentChild)->tick();
    if(s != BH_SUCCESS)return s;
    if(++m_CurrentChild==m_Children.end()) return BH_SUCCESS;
  }
  return BH_INVALID;
}
*/
