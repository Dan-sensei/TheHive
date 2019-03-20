#include "Behavior.hpp"
//#include <iostream>

void Behavior::SetStatus(Status _m_eStatus){
    m_eStatus=_m_eStatus;
}
bool Behavior::isTerminate(){
    if(m_eStatus==BH_RUNNING) return false;
    else return true;



    //BH_INVALID,
    //BH_RUNNING,
    //BH_SUCCESS,
    //BH_FAILURE,
    //BH_SUSPENDED,
    //BH_NEUTRAL
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
