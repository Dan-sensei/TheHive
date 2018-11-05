#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "composite.hpp"


class sequence : public composite{
//public:
 //Status update();
protected:
  behaviors::iterator m_CurrentChild;
 virtual void onInitialize();
  virtual Status update() override{
    while (true) {
      Status s=(*m_CurrentChild)->tick();
      if(s != BH_SUCCESS)return s;
      if(++m_CurrentChild==m_Children.end()) return BH_SUCCESS;
    }
    return  BH_INVALID;
  }

};

#endif /* end of include guard: SEQUENCE_HPP */
