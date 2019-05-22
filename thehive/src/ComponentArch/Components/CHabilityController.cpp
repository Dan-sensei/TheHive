#include "CHabilityController.hpp"
#include <Util.hpp>
#include <string>
//#include <GameAI/Hability.hpp>
#include <Omicron/2D/Motor2D.hpp>
#include <Singleton.hpp>
// #include <Omicron/2D/Motor2D.hpp>


CHabilityController::CHabilityController(){
    hud = Singleton<HUD>::Instance();

    vHabs.emplace_back(&CHabilityController::updateHudCooldown_BM); // Naranha
    vHabs.emplace_back(&CHabilityController::updateHudCooldown_TR); // Asur
    vHabs.emplace_back(&CHabilityController::updateHudCooldown_TL); // Amarilio
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
    Habilities[0] = new Hability1(getEntityID());   // Amarilio
    Habilities[1] = new Hability2(getEntityID());   // Asur
    Habilities[2] = new Hability3(getEntityID());   // Naranha

    return gg::ST_TRUE;
}

void CHabilityController::FixedUpdate(){
    for (size_t i = 0; i < 3; i++) {

        Habilities[i]->update();

        // Singleton<Motor2D>::Instance()->setprogress(i, Habilities[i]->getProg());
        (this->*vHabs[i])(Habilities[i]->getProg());
    }
}

void CHabilityController::updateHudCooldown_TR(const float &cd){
    hud->set_TR_CD(cd);
}

void CHabilityController::updateHudCooldown_TL(const float &cd){
    hud->set_TL_CD(cd);
}

void CHabilityController::updateHudCooldown_BM(const float &cd){
    hud->set_BM_CD(cd);
}
