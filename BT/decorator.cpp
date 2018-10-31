#include "decorator.hpp"

decorator::decorator(behavior* child) : m_pChild(child){
   // Constructor
   std::cout << "Soy el constructor de decorator" << '\n';
}

Status decorator::update(){
   // Ejemplo de decorator repeat
   m_pChild->tick();
   return BH_NEUTRAL;
}

