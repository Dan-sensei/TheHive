#ifndef _CAGENT_H
#define _CAGENT_H

#include <ComponentArch/IComponent.hpp>         // [OBLIGATORIO]
#include <ComponentArch/Message.hpp>            // [OPCIONAL] Si necesitas recibir mensajes o inicializar variables
#include <cstdint>
#include <list>

#include <Util.hpp>
#include <EventSystem/EnumTriggerType.hpp>
#include <EventSystem/CTriggerSystem.hpp>

#include <ComponentArch/Message.hpp>

#include <ComponentArch/Components/CAIEnem.hpp>
#include <Omicron/Omicron.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <Omicron/2D/HUD.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Omicron/AssetManager.hpp>
#include <Singleton.hpp>
#include <BinaryParser.hpp>

#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>




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
        //glm::vec3 vPos;
        void updatetrig();

        bool onTriggerEnter(TriggerRecordStruct* _pRec);
        void onTriggerStay(TriggerRecordStruct* _pRec);
        void onTriggerExit(TriggerRecordStruct* _pRec);

        void SetNextTriggerUpdate(unsigned long _nCurTime);//updatear cada x tiempo
        unsigned long  GetTriggerFlags();
        glm::vec3 GetPosition();
        bool HandleTrig(TriggerRecordStruct* _pRec);//manejar el trigger
        void addAgent(CAgent* agente);
        void removeAgent(std::list <CAgent*>::iterator ite);

        void sonido_0();
        void sonido_1();
        void sonido_2();
        void sonido_3();
        void sonido_4();
        void sonido_5();
        void sonido_6();
        //uint16_t getEntityID();upda

    private:
        Omicron      *Engine;
        CTransform      *cTransform;
        ObjectManager   *oManager;
        AssetManager    *_AssetManager;

        SoundSystem* SS;
        HUD* hud;

        SoundEvent* s_puerta;
        SoundEvent* s_fusible;
        SoundEvent* s_sonidoSaltoPrecipicio;


        using pSonido = void(CAgent::*)();
        pSonido VectorSonidos[7];



        // void getWeaponInformation(float&, float&, float&, float&, int&, int);
        //const std::string &DARTA, int8_t map_zone

        // ---------------------------
        // Lo chido

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
        void ENTER_func_kTrig_ExpansiveForce(TriggerRecordStruct*);
        void ENTER_func_kTrig_EnemyNear     (TriggerRecordStruct*);
        void ENTER_func_kTrig_LoadZone      (TriggerRecordStruct*);
        void ENTER_func_kTrig_UnLoadZone    (TriggerRecordStruct*);
        void ENTER_func_kTrig_InteractMess     (TriggerRecordStruct*);
        void ENTER_func_kTrig_SoundJumpCliff     (TriggerRecordStruct*);

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
        void STAY_func_kTrig_ExpansiveForce (TriggerRecordStruct*);
        void STAY_func_kTrig_EnemyNear      (TriggerRecordStruct*);
        void STAY_func_kTrig_LoadZone       (TriggerRecordStruct*);
        void STAY_func_kTrig_UnLoadZone     (TriggerRecordStruct*);
        void STAY_func_kTrig_InteractMess      (TriggerRecordStruct*);
        void STAY_func_kTrig_SoundJumpCliff       (TriggerRecordStruct*);

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
        void EXIT_func_kTrig_ExpansiveForce (TriggerRecordStruct*);
        void EXIT_func_kTrig_EnemyNear      (TriggerRecordStruct*);
        void EXIT_func_kTrig_LoadZone       (TriggerRecordStruct*);
        void EXIT_func_kTrig_UnLoadZone     (TriggerRecordStruct*);
        void EXIT_func_kTrig_InteractMess      (TriggerRecordStruct*);
        void EXIT_func_kTrig_SoundJumpCliff      (TriggerRecordStruct*);

};

#endif
