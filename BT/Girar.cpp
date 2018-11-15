#include "Girar.hpp"

Girar::Girar(){}
Girar::~Girar(){}

void Girar::onInitialize(){}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Girar::update() {
      std::cout << "Girar update " <<getStatus() << '\n';
      return BH_SUCCESS;
} // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Girar::onTerminate(Status state){
      std::cout << "Girar onTerminate " <<state << '\n';
}
