

#include "Condition.hpp"


Condition::Condition(){}
Condition::~Condition(){}



    void Condition::onInitialize(){//pasar condiciones


    }             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
    Status Condition::update() {
      std::cout << "hoja0 update" <<getStatus() << '\n';
        return BH_SUCCESS;

      }              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
    void Condition::onTerminate(Status state){
      std::cout << "hoja0 onTerminate" <<state << '\n';

    }

 /* BEHAVIOR_HPP */
