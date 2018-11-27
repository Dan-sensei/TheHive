#ifndef RANDOMSEQUENCE_HPP
#define RANDOMSEQUENCE_HPP

#include "Composite.hpp"
#include <cstdint>
#include <iostream>

class RandomSequence : public Composite{
public:
 //Status update();
 RandomSequence();
protected:
    RandomSequence(const RandomSequence &orig);

  Behaviors::iterator m_CurrentChild;
  std::vector<int> secuencia;
  int max;
  virtual void onInitialize();
  virtual Status update();

};

#endif