

#include "sequence.hpp"
sequence::sequence(){}
sequence::~sequence(){}

 void sequence::onInitialize() {
  m_CurrentChild=m_Children.begin();
}
void sequence::onTerminate(Status state){
  std::cout << "sequence onTerminate" << state << '\n';

}
 Status sequence::update() {
  while (true) {
    std::cout << "sequence update" <<getStatus() << '\n';
    Status s=(*m_CurrentChild)->tick();
    if(s != BH_SUCCESS){
      if(s == BH_RUNNING)continue;
      return s;}
    if(++m_CurrentChild==m_Children.end()) return BH_SUCCESS;
  }
  return BH_INVALID;
}
