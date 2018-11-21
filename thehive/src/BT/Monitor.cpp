#include "Monitor.hpp"

void Monitor::addAction(Behavior* hijo){
  m_Children.push_back(hijo);
}

void Monitor::addCondition(Behavior* hijo){
  m_Children.insert(m_Children.begin(),hijo);
}
