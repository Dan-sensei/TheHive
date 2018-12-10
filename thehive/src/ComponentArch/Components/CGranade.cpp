#include "CGranade.hpp"

#define VEL_FACTOR      200.f

CGranade::CGranade(){

}
CGranade::CGranade(float _radius)
:radius(_radius)
{
    begin = std::chrono::high_resolution_clock::now();
}

CGranade::~CGranade() {

}
void CGranade::initComponent() {
    //  We wait for the M_UPDATE message
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::GRANADE, gg::M_UPDATE);
}


void CGranade::Init(){

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

void CGranade::explosion(){
}
gg::EMessageStatus CGranade::MHandler_UPDATE(){
    if(cTransform){

        auto end = std::chrono::high_resolution_clock::now(); //Start de another chrono tu see the processor time now
        auto elapsedtime = end - begin; //The difference between both crhonos is the elapsed time
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count(); //Calculate the elapsed time as milisecons

        if(ms>1200){  //we control the time that we want the granade to move
            explosion();
            Manager->removeEntity(getEntityID());
        }
    }

    return gg::ST_TRUE;
}
