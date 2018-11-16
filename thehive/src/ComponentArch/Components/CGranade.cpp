#include "CGranade.hpp"
#include "CTransform.hpp"

#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>

#include <ComponentArch/InitStructs.hpp>

#include <EventSystem/EnumTriggerType.hpp>
#include "EventSystem/CTriggerSystem.hpp"


CGranade::CGranade() {
    begin = std::chrono::high_resolution_clock::now();
}

CGranade::CGranade(const CGranade &orig){

}

CGranade::~CGranade() {

}
void CGranade::initComponent() {
    //  We wait for the M_UPDATE message
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::GRANADE, gg::M_UPDATE);
}


void CGranade::initializeComponentData(const void* data){

    EventSystem = Singleton<CTriggerSystem>::Instance();
    engine = Singleton<GameEngine>::Instance();
    Manager = Singleton<ObjectManager>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

gg::EMessageStatus CGranade::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}

gg::EMessageStatus CGranade::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CGranade::MHandler_UPDATE(){
    if(cTransform){
        gg::Vector3f currentPosition = cTransform->getPosition();

        auto end = std::chrono::high_resolution_clock::now(); //Start de another chrono tu see the processor time now
        auto elapsedtime = end - begin; //The difference between both crhonos is the elapsed time
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count(); //Calculate the elapsed time as milisecons

        if(ms>1200){  //we control the time that we want the granade to move
            EventSystem->RegisterTriger(kTrig_Explosion,1,0,gg::Vector3f(currentPosition.X,currentPosition.Y,currentPosition.Z), 20, 50,false);
            
            Manager->removeEntity(getEntityID());
        }
    }

    return gg::ST_TRUE;
}
