#ifndef ACTIVESELECTOR_HPP
#define ACTIVESELECTOR_HPP

#include "Selector.hpp"

class ActiveSelector : public Selector {
    private:
    ActiveSelector();
    ~ActiveSelector();
    public:
     virtual Status update();
};
#endif
