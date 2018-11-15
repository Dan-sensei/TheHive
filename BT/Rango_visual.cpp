#include "Rango_visual.hpp"

Rango_visual::Rango_visual(){}
Rango_visual::~Rango_visual(){}

void Rango_visual::onInitialize(){failed=false;}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Rango_visual::update() {
      std::cout << "Andar random update " <<getStatus() << '\n';
      failed =true;
      return BH_SUCCESS;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Rango_visual::onTerminate(Status state){
      std::cout << "Andar random onTerminate " <<state << '\n';
}

void Rango_visual::setFailed(){
        failed=true;
    }
bool Rango_visual::getFailed(){
        return failed;
}
