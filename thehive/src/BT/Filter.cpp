#include "Filter.hpp"

void Filter::addAction(Behavior* hijo){
  m_Children.push_back(hijo);
}
void Filter::addCondition(Behavior* hijo){
  m_Children.insert(m_Children.begin(),hijo);
}
