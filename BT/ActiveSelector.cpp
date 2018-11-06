

#include "ActiveSelector.hpp"


ActiveSelector::ActiveSelector(){

}
ActiveSelector::~ActiveSelector(){

}
 Status ActiveSelector::update(){
  behaviors::iterator prev =m_CurrentChild;
  Selector::onInitialize();
  Status result=Selector::update();
  if(prev != m_Children.end() && m_CurrentChild != prev)(*prev)->abort();//esto puede ser otra cosapkjpi
  return result;

}
