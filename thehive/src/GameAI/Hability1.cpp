#include "Hability1.hpp"
//#include "Enum.hpp"
#include <EventSystem/TData.hpp>
#include <EventSystem/CTriggerSystem.hpp>
#include <ComponentArch/Components/CTransform.hpp>
#include <ComponentArch/Components/CPlayerController.hpp>

#include <Singleton.hpp>

//ultrasonido

    /* data */
    //void Hability::iniciar (Blackboard* _data){
    //    Hability (Blackboard* _data);

    //}
    Hability1::Hability1 (int _id):Hability(_id,0,4000)
    {

    }
    Hability1::Hability1 (){

    }
    Hability1::~Hability1 (){
    }

    Hability1::Hability1 (const Hability1 &orig){


    id=orig.id;
    duracion=orig.duracion;
    cooldown=orig.cooldown;
    nocool=orig.nocool;
    terminado=orig.terminado;
    nTimeStamp=orig.nTimeStamp;
    cTriggerSystem=orig.cTriggerSystem;




}


    //codigo de las habilidades
    void Hability1::Hab1_init (){
        TData mes;
        CTriggerSystem* EventSystem=Singleton<CTriggerSystem>::Instance();

        CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, id));
        float id=cTransform->getEntityID();
        EventSystem->PulsoTrigger(kTrig_Aturd,0,cTransform->getPosition(),500,mes);

    }
