
#ifndef _TData_H
#define _TData_H

#include <map>
#include <iostream>
//#include "Util.hpp"
#include "EventSystem/EnumDataType.hpp"


//static void addAgent(CAgent* agente);
//static void removeAgent(Iterator agente);





class TData{
public:
    ~TData();
    void clin();
    //template <typename T>
    void add(EnumDataType type,float dato);
    TData();
    TData(const TData &orig);
    float find(EnumDataType type);
private:
    std::map <EnumDataType,float>m_dataMap;
    //void operator=(const TData &orig) = delete;


};
//void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}
//unsigned long  CAgent::GetTriggerFlags(){return 0;}
//Vector CAgent::GetPosition(){Vector hola;
//return hola;}
//bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){return true;}
#endif
