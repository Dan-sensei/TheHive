#include "CGranade.hpp"

#define VEL_FACTOR      200.f

CGranade::CGranade(){

}
CGranade::CGranade(float _radius, int time)
:radius(_radius),exTime(time)
{
    begin = std::chrono::high_resolution_clock::now();
}

CGranade::~CGranade() {

}

void CGranade::Init(){

    EventSystem = Singleton<CTriggerSystem>::Instance();
    engine      = Singleton<GameEngine>::Instance();
    Manager     = Singleton<ObjectManager>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

gg::EMessageStatus CGranade::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}

gg::EMessageStatus CGranade::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, getEntityID()));
    cRigidBody = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, getEntityID()));

    return gg::ST_TRUE;
}

void CGranade::explosion(){

}

void CGranade::Update(){
    if(cRigidBody && cRigidBody->checkContactResponse()){

        auto end = std::chrono::high_resolution_clock::now(); //Start de another chrono tu see the processor time now
        auto elapsedtime = end - begin; //The difference between both crhonos is the elapsed time
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count(); //Calculate the elapsed time as milisecons

        if(ms>exTime){  //we control the time that we want the granade to move
            explosion();
            Manager->removeEntity(getEntityID());
        }
    }
}
