#ifndef INVERSO_H
#define INVERSO_H

#include <iostream>
#include "Decorator.hpp"

class Inverso : public Decorator{
    public:
      Inverso(Behavior* _m_pChild);
      Inverso();
      ~Inverso();
      virtual void onTerminate(Status state);
      virtual Status update();
      //virtual void onInitialize();             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
      //virtual void onTerminate(Status);
};
#endif
