#include "Andar_rand.hpp"

Andar_rand::Andar_rand(){}
Andar_rand::~Andar_rand(){}

void Andar_rand::onInitialize(){failed=false;}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Andar_rand::update() {
      std::cout << "Andar random update " <<getStatus() << '\n';
      failed =true;
      return BH_FAILURE;
}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Andar_rand::onTerminate(Status state){
      std::cout << "Andar random onTerminate " <<state << '\n';
}

void Andar_rand::setFailed(){
        failed=true;
    }
bool Andar_rand::getFailed(){
        return failed;
}
