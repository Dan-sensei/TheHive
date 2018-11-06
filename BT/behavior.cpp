

#include "behavior.hpp"

bool behavior::isTerminate(){
if(m_eStatus==BH_RUNNING){
  return false;
}
else{
  return true;

}
}
void behavior::abort(){
m_eStatus=BH_INVALID;
}
   Status behavior::tick(){
      if (m_eStatus != BH_RUNNING) onInitialize();
      m_eStatus = update();
      if (m_eStatus != BH_RUNNING) onTerminate(m_eStatus);
      return m_eStatus;
   }

   Status behavior::getStatus(){
      return m_eStatus;
   }
    void behavior::onInitialize(){}             // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update
    Status behavior::update() {return BH_SUCCESS;}              // Update del comportamiento. Llamado cada vez que el comportamiento es actualizado
    void behavior::onTerminate(Status){}

 /* BEHAVIOR_HPP */
