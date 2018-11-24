#ifndef FILTER_HPP
#define FILTER_HPP

#include "Sequence.hpp"

class Filter : public Sequence{
    //public:
     //Status update();
    protected:
      void addAction(Behavior* hijo);
      void addCondition(Behavior* hijo);
};
#endif
