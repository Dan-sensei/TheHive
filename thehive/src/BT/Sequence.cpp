#include "Sequence.hpp"
Sequence::Sequence(){}
Sequence::~Sequence(){}

void Sequence::onInitialize() {
  m_CurrentChild=m_Children.begin();
}

void Sequence::onTerminate(Status state){
}

Status Sequence::update() {

  while (true) {
    Status s=(*m_CurrentChild)->tick();
    if(s != BH_SUCCESS)//{
      //if(s == BH_RUNNING)continue;
      return s;//}
    if(++m_CurrentChild==m_Children.end()) return BH_SUCCESS;
  }
  return BH_INVALID;
}
