#ifndef _CTRIGGERSYSTEM_H
#define _CTRIGGERSYSTEM_H

#include <map>
#include <iostream>
#include <math.h>
//#include <cstdlib>
//#include <iomanip>
#include <glm/glm.hpp>
//#include <time.h>
#include <sys/time.h>
#include <chrono>

static unsigned long id=0;
#include "Util.hpp"

#include "EnumTriggerType.hpp"
#include "TData.hpp"


//static void addAgent(CAgent* agente);
//static void removeAgent(Iterator agente);

struct TriggerRecordStruct
{
    TriggerRecordStruct(
        EnumTriggerType _eTriggerType,
        unsigned long _idSource,
        const glm::vec3 _vPos,
        float _fRadius,
        unsigned long _fDuration,
        bool _bDynamicSourcePos,
        TData _data
    );
    TriggerRecordStruct(const TriggerRecordStruct &orig);
    glm::vec3 vPos;
    TData data;
    std::chrono::high_resolution_clock::time_point nTimeStamp;
    unsigned long nTriggerID;
    unsigned long idSource;
    unsigned long nExpirationTime;//milliseconds
    float fRadius;
    EnumTriggerType eTriggerType;
    bool bDynamicSourcePos;
};

typedef std::multimap<unsigned short, TriggerRecordStruct*,
                      std::greater <unsigned short> > TRIGGER_MAP;

template <typename T>
class Singleton;

class CTriggerSystem{
    friend class Singleton<CTriggerSystem>;
public:
    ~CTriggerSystem();
    void PulsoTrigger(
        EnumTriggerType _eTriggerType,
        unsigned long _idSource,
        const glm::vec3& _vPos,
        float _fRadius,
        TData _data);
    unsigned long RegisterTriger(
        EnumTriggerType _eTriggerType,
        unsigned long _nPriority,
        unsigned long _idSource,
        const glm::vec3& _vPos,
        float _fRadius,
        float _fDuration,
        bool _bDynamicSourcePos,
        TData _data);

    void clin();



    void RemoveTrigger(unsigned long nTriggerID);
    void Update();

private:
    CTriggerSystem();
    CTriggerSystem(const CTriggerSystem &orig) = delete;
    void operator=(const CTriggerSystem &orig) = delete;

    unsigned long lastIdGiven;

    TRIGGER_MAP m_mapTriggerMap;

    bool m_bTriggerCriticalSection;
};
//void  CAgent::SetNextTriggerUpdate(unsigned long _nCurTime){}
//unsigned long  CAgent::GetTriggerFlags(){return 0;}
//Vector CAgent::GetPosition(){Vector hola;
//return hola;}
//bool CAgent::HandleTrig(TriggerRecordStruct* _pRec){return true;}
#endif
