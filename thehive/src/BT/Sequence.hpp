#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <iostream>
#include "Composite.hpp"

class Sequence : public Composite{
    public:
        //Status update();
        Sequence();
        ~Sequence();
    protected:
        Behaviors::iterator m_CurrentChild;
        virtual void onInitialize();
        virtual void onTerminate(Status state);
        virtual Status update();
};
#endif
