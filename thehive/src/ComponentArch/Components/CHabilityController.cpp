#include "CHabilityController.hpp"
#include <Util.hpp>
#include <string>
//#include <GameAI/Hability.hpp>
#include <GameEngine/Motor2D.hpp>
#include <Singleton.hpp>
// #include <GameEngine/Motor2D.hpp>


CHabilityController::CHabilityController()
//,hab[0](0,2000,4000),hab[1](0,2000,4000),hab[2](0,2000,4000)
{
    //for (int i = 0; i < 3; i++) {
    //    hab[i]=Hability(0,2000,4000);
    //}
}

CHabilityController::~CHabilityController() {
     for (size_t i = 0; i < 3; i++) {

         delete Habilities[i];
     }
}

void CHabilityController::ToggleSkill(int HabilityID){

    Habilities[HabilityID]->init();

}
void CHabilityController::Init(){
    //  We check if this entity has the TRANSFORM component
    MHandler_SETPTRS();

}


gg::EMessageStatus CHabilityController::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CHabilityController::MHandler_SETPTRS(){
    Habilities[0] = new Hability1(getEntityID());
    Habilities[1] = new Hability2(getEntityID());
    Habilities[2] = new Hability3(getEntityID());

    return gg::ST_TRUE;
}

void CHabilityController::FixedUpdate(){
    for (size_t i = 0; i < 3; i++) {

        Habilities[i]->update();
        //Singleton<Motor2D>::Instance()->setprogress(i, Habilities[i]->getProg());
    }
}
