#include "Comer.hpp"

Comer::Comer(){}
Comer::~Comer(){}

void Comer::onInitialize(){}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Comer::update() {
      std::cout << "Comer update " <<getStatus() << '\n';
      return BH_FAILURE;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Comer::onTerminate(Status state){
      std::cout << "Comer onTerminate " <<state << '\n';
}
