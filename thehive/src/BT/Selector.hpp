#ifndef SELECTOR_HPP
#define SELECTOR_HPP

#include "Composite.hpp"

class Selector : public Composite{
     //public:
     //Status update();
    protected:
      Behaviors::iterator m_CurrentChild;
      virtual void onInitialize();
      virtual Status update();
};
#endif
