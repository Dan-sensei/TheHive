

#include "Action.hpp"


Action::Action(){}
Action::~Action(){}



    void Action::onInitialize(){//parámetros del mundo necesatios para el update


    }             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
    Status Action::update() {
      std::cout << "hoja0 update" <<getStatus() << '\n';
        return BH_SUCCESS;

      }              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
    void Action::onTerminate(Status state){//tener cuidado de cerrar todos los recursos que abramos
      std::cout << "hoja0 onTerminate" <<state << '\n';

    }

 /* BEHAVIOR_HPP */
