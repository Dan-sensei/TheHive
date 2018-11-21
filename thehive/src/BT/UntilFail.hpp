#ifndef UNTILFAIL_H
#define UNTILFAIL_H

#include <iostream>
#include "Decorator.hpp"

class UntilFail : public Decorator{
    public:
     Status update();
};
#endif
