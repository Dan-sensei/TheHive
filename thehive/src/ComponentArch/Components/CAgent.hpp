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

#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Singleton.hpp>

class CTransform;

class CAgent : public IComponent {
    public:
        CAgent(const unsigned long &_flags);
        CAgent(const CAgent &orig) = delete;
        virtual ~CAgent();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void Init();         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

        //TriggerRecordStruct holiis;
        std::list  <TriggerRecordStruct*>  holiiis;

        //        void update();
        static void deletetrig(TriggerRecordStruct* _pRec);

        static std::list  <CAgent*>  hola;

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
        //CAgent(unsigned long _dwTriggerFlags,gg::Vector3f _vPos);
        GameEngine* Engine;
        CTransform* cTransform;     //  Punteros a otras componentes

        void getWeaponInformation(float&, float&, float&, float&, int&, int);
};

#endif
