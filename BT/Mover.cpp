#include "Mover.hpp"

Mover::Mover(){}
Mover::~Mover(){}

void Mover::onInitialize(){}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Mover::update() {
      std::cout << "Mover update " <<getStatus() << '\n';
      return BH_FAILURE;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Mover::onTerminate(Status state){
      std::cout << "Mover onTerminate " <<state << '\n';
}
