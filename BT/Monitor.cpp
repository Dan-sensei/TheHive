

#include "Monitor.hpp"



void Monitor::addAction(behavior* hijo){
  m_Children.push_back(hijo);

}
void Monitor::addCondition(behavior* hijo){
  m_Children.insert(m_Children.begin(),hijo);

}
