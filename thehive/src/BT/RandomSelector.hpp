#ifndef RANDOMSELECTOR_HPP
#define RANDOMSELECTOR_HPP

#include "Composite.hpp"
#include <cstdint>
//#include <iostream>

class RandomSelector : public Composite{
public:
 //Status update();
    RandomSelector();
protected:
    RandomSelector(const RandomSelector &orig);
    virtual void onInitialize();
    virtual Status update();
    virtual void onTerminate(Status state);

    Behaviors::iterator m_CurrentChild;
    std::vector<int> secuencia;
    int max;

};

#endif
