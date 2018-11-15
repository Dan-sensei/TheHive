#include "Mover.hpp"

Mover::Mover(){}
Mover::~Mover(){}

void Mover::onInitialize(){failed=false;}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Mover::update() {
      std::cout << "Andar random update " <<getStatus() << '\n';
      failed =true;
      return BH_SUCCESS;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Mover::onTerminate(Status state){
      std::cout << "Andar random onTerminate " <<state << '\n';
}

void Mover::setFailed(){
        failed=true;
    }
bool Mover::getFailed(){
        return failed;
}
