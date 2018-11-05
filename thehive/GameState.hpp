#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <map>
#include <iostream>
#include <math.h>
//#include <cstdlib>
//#include <iomanip>
#include <glm/glm.hpp>
//#include <time.h>
#include <sys/time.h>
static unsigned long id=0;
#include <irrlicht/irrList.h>
#include "Vector.hpp"


enum EnumTriggerType
{
  kTrig_none=0,
  kTrig_Explosion=(1<<0),
  kTrig_EnemyNear=(1<<1),
  kTrig_Gunfire=(1<<2)
};
//static void addAgent(CAgent* agente);
//static void removeAgent(Iterator agente);

struct TriggerRecordStruct
{
  EnumTriggerType eTriggerType;
  unsigned long nTriggerID;
  unsigned long idSource;
  Vector vPos;
  float fRadius;
  unsigned long nTimeStamp;
  unsigned long nExpirationTime;
  bool bDynamicSourcePos;
  TriggerRecordStruct(EnumTriggerType _eTriggerType,unsigned long _idSource,const Vector _vPos,float _fRadius,
                      unsigned long _fDuration,bool _bDynamicSourcePos);


};
typedef std::multimap<unsigned short, TriggerRecordStruct*,
                      std::greater <unsigned short> > TRIGGER_MAP;

template <typename T>
class Singleton;

class CTriggerSystem
{
  friend class Singleton<CTriggerSystem>;
public:
  ~CTriggerSystem();
  unsigned long RegisterTriger(EnumTriggerType _eTriggerType,
  unsigned long _nPriority,unsigned long _idSource,
  const Vector& _vPos, float _fRadius, float _fDuration,
  bool _bDynamicSourcePos);


  void RemoveTrigger(unsigned long nTriggerID);
  void Update();

private:
  CTriggerSystem();
  CTriggerSystem(const CTriggerSystem &orig) = delete;
  void operator=(const CTriggerSystem &orig) = delete;


  TRIGGER_MAP m_mapTriggerMap;

  bool m_bTriggerCriticalSection;
};
//void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}
//unsigned long  CAgent::GetTriggerFlags(){return 0;}
//Vector CAgent::GetPosition(){Vector hola;
//return hola;}
//bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){return true;}
#endif
