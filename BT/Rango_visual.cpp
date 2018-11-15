#include "Rango_visual.hpp"

Rango_visual::Rango_visual(){}
Rango_visual::~Rango_visual(){}

void Rango_visual::onInitialize(){}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Rango_visual::update() {
      std::cout << "Rango_visual update " <<getStatus() << '\n';
      return BH_FAILURE;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Rango_visual::onTerminate(Status state){
      std::cout << "Rango_visual onTerminate " <<state << '\n';
}
