#include "Composite.hpp"
#include <iostream>


void Composite::addChild(Behavior* hijo){
  m_Children.push_back(hijo);
}
Composite::Composite(){}
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
Composite::Composite(const Composite &orig){
    for (size_t i = 0; i < orig.m_Children.size(); i++) {
        m_Children.push_back( m_Children[i]);
    }
}
void Composite::clearChildren(){
    m_Children.clear();
}
Composite::~Composite(){

    //for (size_t i = 0; i < m_Children.size(); i++) {
    //    std::cout << "borrando composite"<< i<< '\n';
    //    if(m_Children[i]!=nullptr){
    //        std::cout << "borrando" << '\n';
    //        //delete m_Children[i];
    //    }
    //}


}
