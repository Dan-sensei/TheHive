#include "Behavior.hpp"
#include <iostream>

bool Behavior::isTerminate(){
    if(m_eStatus==BH_RUNNING) return false;
    else return true;
}
Behavior::~Behavior(){

}

void Behavior::abort(){
    m_eStatus=BH_INVALID;
}
Status Behavior::tick(){
    if (m_eStatus != BH_RUNNING) {
      m_eStatus = BH_RUNNING;
      onInitialize();
    }

    m_eStatus = update();
//std::cout << "estatus final" << m_eStatus<< '\n';
    if (m_eStatus != BH_RUNNING) onTerminate(m_eStatus);

    return m_eStatus;
}

Status Behavior::getStatus(){
    return m_eStatus;
}

void Behavior::onInitialize(){

}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
Status Behavior::update() {return BH_SUCCESS;}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
void Behavior::onTerminate(Status){}
