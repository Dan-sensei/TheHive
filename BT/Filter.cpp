

#include "Filter.hpp"



void Filter::addAction(behavior* hijo){
  m_Children.push_back(hijo);

}
void Filter::addCondition(behavior* hijo){
  m_Children.insert(m_Children.begin(),hijo);

}
