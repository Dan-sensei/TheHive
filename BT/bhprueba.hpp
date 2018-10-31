#ifndef BHPRUEBA_HPP
#define BHPRUEBA_HPP

/*
bhprueba es un behavior que hereda de la interfaz behavior.hpp
*/
#include <iostream>

#include "behavior.hpp"

class bhprueba : public behavior{
private:
   Status m_eStatus;
   int aux;
public:
   bhprueba();
   void onInitialize();
   Status update();
   void onTerminate(Status);
};



#endif /* end of include guard: BHPRUEBA_HPP */
