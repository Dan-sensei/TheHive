#ifndef Filter_HPP
#define Filter_HPP

#include "sequence.hpp"


class Filter : public sequence{
//public:
 //Status update();
protected:
  void addAction(behavior* hijo);
  void addCondition(behavior* hijo);

};

#endif /* end of include guard: SEQUENCE_HPP */
