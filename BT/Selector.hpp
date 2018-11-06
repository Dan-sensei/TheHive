#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "composite.hpp"


class Selector : public composite{
//public:
 //Status update();
protected:
  behaviors::iterator m_CurrentChild;
 virtual void onInitialize();
  virtual Status update();

};

#endif /* end of include guard: SEQUENCE_HPP */
