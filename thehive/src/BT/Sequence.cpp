#include "Sequence.hpp"
Sequence::Sequence(){}
Sequence::~Sequence(){}

void Sequence::onInitialize() {
    //std::cout << "init sequence" << '\n';

  m_CurrentChild=m_Children.begin();
}

void Sequence::onTerminate(Status state){
    //std::cout << "terminate sequence" <<state<< '\n';

  //std::cout << "Sequence onTerminate" << state << '\n';
}

Status Sequence::update() {
    //std::cout << "update sequence" << '\n';

  while (true) {
    //std::cout << "Sequence update" <<getStatus() << '\n';
    Status s=(*m_CurrentChild)->tick();
    if(s != BH_SUCCESS)//{
      //if(s == BH_RUNNING)continue;
      return s;//}
    if(++m_CurrentChild==m_Children.end()) return BH_SUCCESS;
  }
  return BH_INVALID;
}
