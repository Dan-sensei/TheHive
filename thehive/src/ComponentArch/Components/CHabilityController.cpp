#include "CHabilityController.hpp"
#include <Util.hpp>
#include <string>
//#include <GameAI/Hability.hpp>
#include <GameEngine/ScreenConsole.hpp>
#include <Singleton.hpp>
// #include <GameEngine/ScreenConsole.hpp>


CHabilityController::CHabilityController()
//,hab[0](0,2000,4000),hab[1](0,2000,4000),hab[2](0,2000,4000)
{
    //for (int i = 0; i < 3; i++) {
    //    hab[i]=Hability(0,2000,4000);
    //}
}

CHabilityController::~CHabilityController() {
    for (size_t i = 0; i < 3; i++) {

        delete hab[i];
    }
}

void CHabilityController::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::HAB, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::HAB, gg::M_SETPTRS);

}

void CHabilityController::pulsado(int habi){

    hab[habi]->init();

}
void CHabilityController::Init(){
    //  We check if this entity has the TRANSFORM component
    MHandler_SETPTRS();

}


gg::EMessageStatus CHabilityController::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CHabilityController::MHandler_SETPTRS(){
    hab[0]=new Hability1(getEntityID());
    hab[1]=new Hability2(getEntityID());
    hab[2]=new Hability3(getEntityID());

    return gg::ST_TRUE;
}

gg::EMessageStatus CHabilityController::MHandler_UPDATE(){
    for (size_t i = 0; i < 3; i++) {

        hab[i]->update();
        Singleton<ScreenConsole>::Instance()->setprogress(i,hab[i]->getProg());
    }


    return gg::ST_TRUE;

}