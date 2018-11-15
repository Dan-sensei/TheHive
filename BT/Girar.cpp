#include "Girar.hpp"

Girar::Girar(){}
Girar::~Girar(){}

void Girar::onInitialize(){failed=false;}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Girar::update() {
      std::cout << "Andar random update " <<getStatus() << '\n';
      failed =true;
      return BH_SUCCESS;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Girar::onTerminate(Status state){
      std::cout << "Andar random onTerminate " <<state << '\n';
}

void Girar::setFailed(){
        failed=true;
    }
bool Girar::getFailed(){
        return failed;
}
