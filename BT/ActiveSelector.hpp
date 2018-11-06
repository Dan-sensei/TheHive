#ifndef ActiveSelector_HPP
#define ActiveSelector_HPP

#include "Selector.hpp"


class ActiveSelector : public Selector{
ActiveSelector();
~ActiveSelector();
public:
 virtual Status update();

};

#endif /* end of include guard: SEQUENCE_HPP */
