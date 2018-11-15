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
#include "ComponentArch/Components/CAgent.hpp"
#include <EventSystem/CTriggerSystem.hpp>


CTriggerSystem::CTriggerSystem(){
    lastIdGiven = 0;
}
CTriggerSystem::~CTriggerSystem(){}

unsigned long CTriggerSystem::RegisterTriger(
    EnumTriggerType _eTriggerType,
    unsigned long _nPriority,
    unsigned long _idSource,
    const gg::Vector3f& _vPos,
    float _fRadius,
    float _fDuration,
    bool _bDynamicSourcePos)
{
    //Create a trigger record, and fill it in
    TriggerRecordStruct* pTriggerRecord = new TriggerRecordStruct(_eTriggerType,_idSource,_vPos,_fRadius,_fDuration,_bDynamicSourcePos);
    lastIdGiven++;

    //Trigger records are sorted by priority
    m_mapTriggerMap.insert(TRIGGER_MAP::value_type(_nPriority,pTriggerRecord));

    //return unique id for this triger
    return pTriggerRecord->nTriggerID;
}


void CTriggerSystem::RemoveTrigger(unsigned long nTriggerID)
{
  TRIGGER_MAP::iterator it=m_mapTriggerMap.begin();
  while(it!=m_mapTriggerMap.end()){
    if(it->second->nTriggerID == nTriggerID){
      delete(it->second);
      return;
    }
    else ++it;

  }
}

void CTriggerSystem::Update()
{

  CAgent* pAgent=NULL;
  float fDistance=0.f;

  TriggerRecordStruct* pRec;
  TRIGGER_MAP::iterator it;
  //unsigned long nCurTime = Time::timeGetTime();
  std::chrono::high_resolution_clock::time_point nCurTime = std::chrono::high_resolution_clock::now();

  //unsigned long nCurTime = 0;
  //Delete expired trigger records. For records tha are not
  //expired, update position if the dynamic flag is set
  it =m_mapTriggerMap.begin();
  while(it!=m_mapTriggerMap.end())
  {
    pRec = it->second;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(nCurTime - pRec->nTimeStamp).count();

    if( (pRec->nExpirationTime!=0)&&
        (pRec->nExpirationTime < ms))
        {
          delete(pRec);
          it=m_mapTriggerMap.erase(it);

        }else{
          //Update pos if dynamic flag is set.Reset time-stamp
          if(pRec->bDynamicSourcePos==true)
          {
            //Update(pRec->vPos);//funcion para actualizar la posicion
            //pRec->nTimeStamp = nCurTime;
          }
          ++it;
        }
  }
  //Trigger agents
  //int g_nNumAgents=20;//numero actual de agentes
  std::list<CAgent*>::iterator it2 ;
  it2=CAgent::hola.begin();
  for(unsigned long i=0; i<CAgent::hola.size();++i)
  {
    pAgent=*it2;
    //pAgent->SetNextTriggerUpdate(nCurTime);
    //llop thru exixting trigger records
    //// std::cout << "agente" << pAgent->nCAgentID << "("<<pAgent->GetPosition().X<<"," <<pAgent->GetPosition().Y<<","<<pAgent->GetPosition().Z<<")"<< '\n';
    //// std::cout << "agente" << pAgent->nCAgentID << "con triger"<< pAgent->GetTriggerFlags()<<'\n';


    for(it=m_mapTriggerMap.begin();
        it!=m_mapTriggerMap.end();++it)
    {

      pRec=it->second;
     // // std::cout << "trigger" << pRec->idSource << "("<<pRec->vPos.X<<"," <<pRec->vPos.Y<<","<<pRec->vPos.Z<<")"<< '\n';

      //Does agent respond to trigger?
      if(!(pRec->eTriggerType & pAgent->GetTriggerFlags()))
        continue;
      //is source the agent itself?
      if(pRec->idSource==pAgent->nCAgentID)
        continue;
      //Check radius
      //
      fDistance=gg::Util::DIST(pRec->vPos,pAgent->GetPosition());//funcion calcular la distancia
      if(fDistance > pRec->fRadius)
        continue;
      //handletriger return true if the agent responded
      //to the trigger
      if(pAgent->HandleTrig(pRec))
      {
          // // std::cout << "agente" << pAgent->nCAgentID << "con triger"<< pAgent->GetTriggerFlags()<<'\n';

        //Listen to highest priority trig at any instant
        break;
      }
    }
    it2++;
  }
}

TriggerRecordStruct::TriggerRecordStruct(
    EnumTriggerType     _eTriggerType,
    unsigned long       _idSource,
    const gg::Vector3f  _vPos,
    float               _fRadius,
    unsigned long       _fDuration,
    bool                _bDynamicSourcePos)
{
    eTriggerType=_eTriggerType;
    nTriggerID=id;
    // id++;
    idSource=_idSource;
    vPos=_vPos;
    fRadius=_fRadius;

    std::chrono::high_resolution_clock::time_point  begin = std::chrono::high_resolution_clock::now();


    nTimeStamp=std::chrono::high_resolution_clock::now();;// eso o sucedaneo
    nExpirationTime=_fDuration;
    bDynamicSourcePos=_bDynamicSourcePos;
}

void CTriggerSystem::clin(){
    TRIGGER_MAP::iterator it=m_mapTriggerMap.begin();
    while(it!=m_mapTriggerMap.end()){
        delete(it->second);
        ++it;
    }
}

//Pruebas
//unsigned long CTriggerSystem::RegisterTriger(
//  EnumTriggerType _eTriggerType, unsigned long _nPriority,
//  unsigned long _idSource,const Vector& _vPos, float _fRadius,
//  float _fDuration,bool _bDynamicSourcePos){return 0;}
//void CTriggerSystem::RemoveTrigger(unsigned long nTriggerID){}
//void CTriggerSystem::Update(){}
