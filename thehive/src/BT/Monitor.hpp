#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "Parallel.hpp"

class Monitor : public Parallel{
    //public:
     //Status update();
    protected:
      void addAction(Behavior* hijo);
      void addCondition(Behavior* hijo);
};
#endif
