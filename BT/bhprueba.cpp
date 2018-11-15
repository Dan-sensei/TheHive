#include "bhprueba.hpp"

bhprueba::bhprueba(){
   // std::cout << "Soy el constructor de bhprueba. STATUS: " << m_eStatus << std::endl;
   m_eStatus = BH_INVALID; // Inicializo el estado
   aux = 5;                // Prueba
}

void bhprueba::onInitialize(){
   // std::cout << "---  Inicializo bhprueba" << std::endl;
   m_eStatus = BH_RUNNING;
}

Status bhprueba::update(){
   // std::cout << "Soy el update " << aux << " de bhprueba" << std::endl;
   aux--;

   if(aux){
      return BH_RUNNING;
   }
   else{
      return BH_FAILURE;
   }
}

void bhprueba::onTerminate(Status){
   // std::cout << "---  Termino bhprueba" << std::endl;
}