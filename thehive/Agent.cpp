//#include <iostream>
//mio
//#include <cstdlib>
//#include <stdio.h>
//#include <stdlib.h>
//#include <termios.h>
//#include <term.h>
//#include <curses.h>
//#include <unistd.h>
//#include <vector>
#include "Agent.hpp"
#include "Vector.hpp"
#include "Time.hpp"

irr::core::list <CAgent*>  CAgent::hola;


void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}
unsigned long  CAgent::GetTriggerFlags(){return dwTriggerFlags;}
Vector CAgent::GetPosition(){return vPos;}
bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){

  std::cout << "Id agente:"<<nCAgentID << " ha entrado"<<std::endl;

  return true;}


void CAgent::addAgent(CAgent* agente){
  hola.push_back(agente);
}
void CAgent::removeAgent(irr::core::list<CAgent*>::Iterator ite){
  hola.erase(ite);
}
//static irr::core::list <CAgent*>  hola;
