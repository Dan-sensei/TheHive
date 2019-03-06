#ifndef UNTILFAIL_H
#define UNTILFAIL_H

#include <iostream>
#include "Decorator.hpp"

class UntilFail : public Decorator{
    public:
        UntilFail(Behavior* _m_pChild);
        UntilFail();
        virtual ~UntilFail();
        virtual void onTerminate(Status state);
        virtual Status update();
};
#endif
