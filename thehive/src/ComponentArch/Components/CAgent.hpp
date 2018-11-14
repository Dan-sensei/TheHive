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


                                                //            punteros a otras componentes


class GameEngine;        //  [OPCIONAL] Si necesitas acceder a algún método de GameEngine
class ObjectManager;     //  [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

class CTransform;           //  Forward declaration de otras componentes que incluyas

class CAgent : public IComponent {
    friend class ObjectManager;                 // Con esto le decimos que sólo ObjectManager puede crear esta componente
    public:



        static std::list  <CAgent*>  hola;

        uint16_t nCAgentID;
        unsigned long dwTriggerFlags;
        unsigned long nDeltaTime;
        //gg::Vector3f vPos;
        void SetNextTriggerUpdate(unsigned long _nCurTime);//updatear cada x tiempo
        unsigned long  GetTriggerFlags();
        gg::Vector3f GetPosition();
        bool HandleTrig(TriggerRecordStruct* _pRec);//manejar el trigger
        void addAgent(CAgent* agente);
        void removeAgent(std::list <CAgent*>::iterator ite);
        //uint16_t getEntityID();

        virtual ~CAgent();

        // Functions of IComponent
        static void initComponent();
        virtual gg::EMessageStatus processMessage(const Message &m);    // [OPCIONAL] (Obligatorio si referencias a otras componentes)
        virtual void initializeComponentData(const void* data);         // [OBLIGATORIO] Aunque esté vacío en el .cpp

        // Handlers                                 // Funciones que se llaman dependiendo del mensaje que recibas
        gg::EMessageStatus MHandler_SETPTRS ();     // IMPORTANTE: SETPTRS Se usará para inicializar punteros a otras componentes
        gg::EMessageStatus MHandler_UPDATE  ();

    private:
        CAgent();                //  No queremos que alguien lo construya fuera (Limón)
        CAgent(const CAgent &orig) = delete;
        //CAgent(unsigned long _dwTriggerFlags,gg::Vector3f _vPos);



        GameEngine* engine;

        CTransform* cTransform;     //  Punteros a otras componentes

};

#endif
