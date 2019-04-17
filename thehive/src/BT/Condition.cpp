#include "Condition.hpp"

Condition::Condition(){}
Condition::~Condition(){}

void Condition::onInitialize(){}//pasar condiciones Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Condition::update() { // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
    return BH_SUCCESS;
}

void Condition::onTerminate(Status state){
}
