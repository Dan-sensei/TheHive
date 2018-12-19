#ifndef _CAGENT_H
#define _CAGENT_H

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
#include <cstdint>
#include <list>
//#include <irrlicht>

#include <Util.hpp>
#include <EventSystem/EnumTriggerType.hpp>
#include <EventSystem/CTriggerSystem.hpp>

#include <ComponentArch/Message.hpp>

#include <ComponentArch/Components/CAIEnem.hpp>
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Singleton.hpp>


class CTransform;
class CVida;

class CAgent : public IComponent {
    public:
        CAgent(const unsigned long &_flags);
        CAgent(const CAgent &orig) = delete;
        virtual ~CAgent();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();
        //virtual void Update();

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes

        //TriggerRecordStruct holiis;
        std::list  <TriggerRecordStruct*>  TriggerList;

        //        void update();
        static void deletetrig(TriggerRecordStruct* _pRec);

        static std::list  <CAgent*>  AgentList;

        uint16_t nCAgentID;
        unsigned long dwTriggerFlags;
        unsigned long nDeltaTime;
        //gg::Vector3f vPos;
        void updatetrig();

        bool onTriggerEnter(TriggerRecordStruct* _pRec);
        void onTriggerStay(TriggerRecordStruct* _pRec);
        void onTriggerExit(TriggerRecordStruct* _pRec);

        void SetNextTriggerUpdate(unsigned long _nCurTime);//updatear cada x tiempo
        unsigned long  GetTriggerFlags();
        gg::Vector3f GetPosition();
        bool HandleTrig(TriggerRecordStruct* _pRec);//manejar el trigger
        void addAgent(CAgent* agente);
        void removeAgent(std::list <CAgent*>::iterator ite);
        //uint16_t getEntityID();upda

    private:
        GameEngine      *Engine;
        CTransform      *cTransform;
        ObjectManager   *oManager;

        void getWeaponInformation(float&, float&, float&, float&, int&, int);

        std::map<EnumTriggerType, void (CAgent::*)(TriggerRecordStruct*)> mapFuncOnTriggerEnter;
        void ENTER_func_kTrig_none          (TriggerRecordStruct*);
        void ENTER_func_kTrig_Explosion     (TriggerRecordStruct*);
        void ENTER_func_kTrig_Gunfire       (TriggerRecordStruct*);
        void ENTER_func_kTrig_Shoot         (TriggerRecordStruct*);
        void ENTER_func_kTrig_Touchable     (TriggerRecordStruct*);
        void ENTER_func_kTrig_Senyuelo      (TriggerRecordStruct*);
        void ENTER_func_kTrig_Aturd         (TriggerRecordStruct*);
        void ENTER_func_kTrig_Pickable      (TriggerRecordStruct*);
        void ENTER_func_kTrig_DeadAlien     (TriggerRecordStruct*);
        void ENTER_func_kTrig_ExpansiveWave (TriggerRecordStruct*);
        void ENTER_func_kTrig_EnemyNear     (TriggerRecordStruct*);

        std::map<EnumTriggerType, void (CAgent::*)(TriggerRecordStruct*)> mapFuncOnTriggerStay;
        void STAY_func_kTrig_none           (TriggerRecordStruct*);
        void STAY_func_kTrig_Explosion      (TriggerRecordStruct*);
        void STAY_func_kTrig_Gunfire        (TriggerRecordStruct*);
        void STAY_func_kTrig_Shoot          (TriggerRecordStruct*);
        void STAY_func_kTrig_Touchable      (TriggerRecordStruct*);
        void STAY_func_kTrig_Senyuelo       (TriggerRecordStruct*);
        void STAY_func_kTrig_Aturd          (TriggerRecordStruct*);
        void STAY_func_kTrig_Pickable       (TriggerRecordStruct*);
        void STAY_func_kTrig_DeadAlien      (TriggerRecordStruct*);
        void STAY_func_kTrig_ExpansiveWave  (TriggerRecordStruct*);
        void STAY_func_kTrig_EnemyNear      (TriggerRecordStruct*);

        std::map<EnumTriggerType, void (CAgent::*)(TriggerRecordStruct*)> mapFuncOnTriggerExit;
        void EXIT_func_kTrig_none           (TriggerRecordStruct*);
        void EXIT_func_kTrig_Explosion      (TriggerRecordStruct*);
        void EXIT_func_kTrig_Gunfire        (TriggerRecordStruct*);
        void EXIT_func_kTrig_Shoot          (TriggerRecordStruct*);
        void EXIT_func_kTrig_Touchable      (TriggerRecordStruct*);
        void EXIT_func_kTrig_Senyuelo       (TriggerRecordStruct*);
        void EXIT_func_kTrig_Aturd          (TriggerRecordStruct*);
        void EXIT_func_kTrig_Pickable       (TriggerRecordStruct*);
        void EXIT_func_kTrig_DeadAlien      (TriggerRecordStruct*);
        void EXIT_func_kTrig_ExpansiveWave  (TriggerRecordStruct*);
        void EXIT_func_kTrig_EnemyNear      (TriggerRecordStruct*);

};

#endif
