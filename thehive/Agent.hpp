#ifndef _AGENT_H
#define _AGENT_H

#include <map>
#include <iostream>
#include <math.h>
//#include <cstdlib>
//#include <iomanip>
#include <glm/glm.hpp>
//#include <time.h>
#include <sys/time.h>
static unsigned long id2=0;
#include <irrlicht/irrList.h>
#include "GameState.hpp"



class CAgent
{
public:
  CAgent(unsigned long _dwTriggerFlags,Vector _vPos){
    nCAgentID=id2;
    id2++;
    dwTriggerFlags=_dwTriggerFlags;
    nDeltaTime=0;
    vPos=_vPos;
  }
  CAgent(){

  }
  ~CAgent(){

  }
  static irr::core::list <CAgent*>  hola;
  
  unsigned long nCAgentID;
  unsigned long dwTriggerFlags;
  unsigned long nDeltaTime;
  Vector vPos;
  void SetNextTriggerUpdate(unsigned long _nCurTime);
  unsigned long  GetTriggerFlags();
  Vector GetPosition();
  bool HandleTrig(TriggerRecordStruct* _pRec);
  void addAgent(CAgent* agente);
  void removeAgent(irr::core::list<CAgent*>::Iterator ite);
private:
};

//void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}
//unsigned long  CAgent::GetTriggerFlags(){return 0;}
//Vector CAgent::GetPosition(){Vector hola;
//return hola;}
//bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){return true;}
#endif
