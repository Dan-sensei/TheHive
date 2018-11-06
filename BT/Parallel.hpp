#ifndef Parallel_HPP
#define Parallel_HPP
#include <iostream>

#include "composite.hpp"


class Parallel : public composite{
public:
 //Status update();
 enum Policy{
   RequireOne,
   RequireAll,
 };
 Parallel(Policy succes,Policy failure);

 Parallel();
 ~Parallel();
protected:
  Policy m_eSuccesPolicy;
  Policy m_eFailurePolicy;
  
 virtual void onInitialize();
 virtual void onTerminate(Status state);
  virtual Status update();

};

#endif /* end of include guard: SEQUENCE_HPP */
