#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <map>
#include <iostream>
#include <math.h>

#include <glm/glm.hpp>
//#include <time.h>
#include <sys/time.h>
static unsigned long timeGetTime();
static unsigned long id=0;
static unsigned long id2=0;


enum EnumTriggerType
{
  kTrig_none=0,
  kTrig_Explosion=(1<<0),
  kTrig_EnemyNear=(1<<1),
  kTrig_Gunfire=(1<<2)
};
struct Vector
{
  //glm::vec3 V3;
  float x;
  float y;
  float z;
  Vector();
  Vector(float _x,float _y, float _z);
  //glm::vec3 aVector(3);
};
static float DIST(Vector v1,Vector v2);
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

class CTriggerSystem
{
public:
  CTriggerSystem();
  ~CTriggerSystem();
  unsigned long RegisterTriger(EnumTriggerType _eTriggerType,
  unsigned long _nPriority,unsigned long _idSource,
  const Vector& _vPos, float _fRadius, float _fDuration,
  bool _bDynamicSourcePos);


  void RemoveTrigger(unsigned long nTriggerID);
  void Update();

private:
  TRIGGER_MAP m_mapTriggerMap;

  bool m_bTriggerCriticalSection;
};
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
  CAgent();
  ~CAgent();
  unsigned long nCAgentID;
  unsigned long dwTriggerFlags;
  unsigned long nDeltaTime;
  Vector vPos;
  void SetNextTriggerUpdate(unsigned long _nCurTime);
  unsigned long  GetTriggerFlags();
  Vector GetPosition();
  bool HandleTrig(TriggerRecordStruct* _pRec);
private:
};
//void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}
//unsigned long  CAgent::GetTriggerFlags(){return 0;}
//Vector CAgent::GetPosition(){Vector hola;
//return hola;}
//bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){return true;}
#endif
