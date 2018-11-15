#include "Comer.hpp"

Comer::Comer(){}
Comer::~Comer(){}

void Comer::onInitialize(){failed=false;}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Comer::update() {
      std::cout << "Andar random update " <<getStatus() << '\n';
      failed =true;
      return BH_SUCCESS;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Comer::onTerminate(Status state){
      std::cout << "Andar random onTerminate " <<state << '\n';
}

void Comer::setFailed(){
        failed=true;
    }
bool Comer::getFailed(){
        return failed;
}
