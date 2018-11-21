#ifndef SUCCEEDER_H
#define SUCCEEDER_H

#include <iostream>
#include "Decorator.hpp"

class Succeeder : public Decorator{
    public:
        Status update();
};
#endif
