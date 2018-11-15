#ifndef RANDOMSELECTOR_HPP
#define RANDOMSELECTOR_HPP

#include "Composite.hpp"
#include <iostream>

class RandomSelector : public Composite{
//public:
 //Status update();
protected:
  Behaviors::iterator m_CurrentChild;
  int secuencia[10];
  int cont;
  virtual void onInitialize();
  virtual Status update();

};

#endif
