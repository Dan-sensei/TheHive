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
#include "Util.hpp"

//SetNextTriggerUpdate hacer que los agentes solo vean los triggers cada cierto tiempo


class CAgent
{
public:
  CAgent(unsigned long _dwTriggerFlags,gg::Vector3f _vPos);
  CAgent();
  ~CAgent();
  static irr::core::list <CAgent*>  hola;

  unsigned long nCAgentID;
  unsigned long dwTriggerFlags;
  unsigned long nDeltaTime;
  gg::Vector3f vPos;
  void SetNextTriggerUpdate(unsigned long _nCurTime);
  unsigned long  GetTriggerFlags();
  gg::Vector3f GetPosition();
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
