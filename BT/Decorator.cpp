#include "Decorator.hpp"

Decorator::Decorator(Behavior* _m_pChild){
  m_pChild=_m_pChild;
}

Decorator::Decorator(){}
Decorator::~Decorator(){}
