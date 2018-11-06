

#include "hoja0.hpp"


hoja0::hoja0(){}
hoja0::~hoja0(){}



    void hoja0::onInitialize(){
      contador=0;


    }             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
    Status hoja0::update() {
      std::cout << "hoja0 update" <<getStatus() << '\n';
      contador++;
      if(contador!=3){
        return BH_RUNNING;
      }else{
        return BH_SUCCESS;
      }

      }              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
    void hoja0::onTerminate(Status state){
      std::cout << "hoja0 onTerminate" <<state << '\n';

    }

 /* BEHAVIOR_HPP */
