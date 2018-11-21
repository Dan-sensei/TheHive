#ifndef RANDOMSELECTOR_HPP
#define RANDOMSELECTOR_HPP

#include "Composite.hpp"
#include <cstdint>
#include <iostream>

class RandomSelector : public Composite{
//public:
 //Status update();
protected:
  Behaviors::iterator m_CurrentChild;
  std::vector<int> secuencia;
  int max;
  virtual void onInitialize();
  virtual Status update();
  virtual void onTerminate(Status state);


};

#endif
