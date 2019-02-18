#ifndef PARALLEL_HPP
#define PARALLEL_HPP

#include <iostream>
#include "Composite.hpp"

enum Policy{
    RequireOne,
    RequireAll,
};
class Parallel : public Composite{
    public:
     //Status update();
     Parallel(Policy succes,Policy failure);

     Parallel();
     ~Parallel();

    protected:
      virtual void onInitialize();
      virtual void onTerminate(Status state);
      virtual Status update();

      Policy m_eSuccesPolicy;
      Policy m_eFailurePolicy;
};
#endif
