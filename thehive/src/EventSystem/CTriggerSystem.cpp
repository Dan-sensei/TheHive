#include "ComponentArch/ObjectManager.hpp"
#include "ComponentArch/Components/CAgent.hpp"
#include "ComponentArch/Components/CTransform.hpp"

#include <EventSystem/CTriggerSystem.hpp>
#include <EventSystem/EnumDataType.hpp>

#include "Singleton.hpp"


TriggerRecordStruct::TriggerRecordStruct(const TriggerRecordStruct &orig){
    data=orig.data;
    eTriggerType=orig.eTriggerType;
    vPos=orig.vPos;
    nTriggerID=orig.nTriggerID;
    idSource=orig.idSource;
    nTimeStamp=orig.nTimeStamp;
    nExpirationTime=orig.nExpirationTime;//milliseconds
    fRadius=orig.fRadius;
    bDynamicSourcePos=orig.bDynamicSourcePos;
}

CTriggerSystem::CTriggerSystem(){
    lastIdGiven = 0;
}

CTriggerSystem::~CTriggerSystem(){}

void CTriggerSystem::PulsoTrigger(
    EnumTriggerType _eTriggerType,
    unsigned long _idSource,
    const gg::Vector3f& _vPos,
    float _fRadius,
    TData _data)
    {
        CAgent* pAgent=NULL;
        float fDistance=0.f;

        TriggerRecordStruct pRec(_eTriggerType,_idSource,_vPos,_fRadius,0,false,_data);
        std::list<CAgent*>::iterator it2;
        it2=CAgent::hola.begin();
        for(unsigned long i=0; i<CAgent::hola.size();++i,it2++){
            pAgent=*it2;

            //Does agent respond to trigger?
            if(!(pRec.eTriggerType & pAgent->GetTriggerFlags()))
                continue;

            //is source the agent itself?
            if(pRec.idSource==pAgent->nCAgentID)
                continue;

            //Check radius
            //
            fDistance=gg::DIST(pRec.vPos,pAgent->GetPosition());//funcion calcular la distancia
            if(fDistance > pRec.fRadius)
                continue;

            //handletriger return true if the agent responded
            //to the trigger
            pAgent->onTriggerEnter(&pRec);

      }
}

unsigned long CTriggerSystem::RegisterTriger(
    EnumTriggerType _eTriggerType,
    unsigned long _nPriority,
    unsigned long _idSource,
    const gg::Vector3f& _vPos,
    float _fRadius,
    float _fDuration,
    bool _bDynamicSourcePos,
    TData _data)
{
//std::map<EnumDataType,float>::iterator it;
//it = _data.m_dataMap.find(kDat_Damage);
//  if (it != _data.m_dataMap.end())
//    _data.m_dataMap.erase (it);


    //Create a trigger record, and fill it in
    TriggerRecordStruct* pTriggerRecord = new TriggerRecordStruct(_eTriggerType,_idSource,_vPos,_fRadius,_fDuration,_bDynamicSourcePos,_data);

    //MessageXplotato* exp =(MessageXplotato*) pTriggerRecord->data;
    //MessageXplotato* exp =(MessageXplotato*) pTriggerRecord->data;

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
            //if(pRec->eTriggerType & kTrig_Explosion){
            //    MessageXplotato* exp =(MessageXplotato*) pRec->data;
            //    delete exp ;
            //}
            CAgent::deletetrig(pRec);
            delete(pRec);
            it=m_mapTriggerMap.erase(it);

        }else{
          //Update pos if dynamic flag is set.Reset time-stamp
          if(pRec->bDynamicSourcePos==true){
              CTransform *ct = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, pRec->idSource));
              if(ct){
                  pRec->vPos = ct->getPosition();
              }
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
    //hacer update eliminar
    pAgent->updatetrig();


    //auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(nCurTime - pRec->nTimeStamp).count();
    //if(pAgent->SetNextTriggerUpdate(nCurTime))...
    //pAgent->SetNextTriggerUpdate(nCurTime);//usado para controlar el ratio de update
    //llop thru exixting trigger records


    for(it=m_mapTriggerMap.begin();
        it!=m_mapTriggerMap.end();++it)
    {

      pRec=it->second;

      //Does agent respond to trigger?
      if(!(pRec->eTriggerType & pAgent->GetTriggerFlags()))
        continue;
      //is source the agent itself?
      if(pRec->idSource==pAgent->nCAgentID)
        continue;
      //Check radius
      //
      fDistance=gg::DIST(pRec->vPos,pAgent->GetPosition());//funcion calcular la distancia
      if(fDistance > pRec->fRadius)
        continue;
      //handletriger return true if the agent responded
      //to the trigger
      if(pAgent->HandleTrig(pRec))
      {


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
    bool                _bDynamicSourcePos,
    TData               _data)
{
    data=_data;
    eTriggerType=_eTriggerType;
    nTriggerID=id;
    // id++;
    idSource=_idSource;
    vPos=_vPos;
    fRadius=_fRadius;

    std::chrono::high_resolution_clock::time_point  begin = std::chrono::high_resolution_clock::now();


    nTimeStamp=std::chrono::high_resolution_clock::now();// eso o sucedaneo
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
