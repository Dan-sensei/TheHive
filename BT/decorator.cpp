#include "decorator.hpp"

decorator::decorator(behavior* _m_pChild){
  m_pChild=_m_pChild;
   // Constructor
  // std::cout << "Soy el constructor de decorator" << '\n';
}

//Status decorator::update(){
//   // Ejemplo de decorator repeat
//   m_pChild->tick();
//   return BH_NEUTRAL;
//}
decorator::decorator(){}
decorator::~decorator(){}
