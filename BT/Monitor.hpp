#ifndef Monitor_HPP
#define Monitor_HPP

#include "Parallel.hpp"


class Monitor : public Parallel{
//public:
 //Status update();
protected:
  void addAction(behavior* hijo);
  void addCondition(behavior* hijo);

};

#endif /* end of include guard: SEQUENCE_HPP */
