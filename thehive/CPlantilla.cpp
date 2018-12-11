#include "CPlantilla.hpp"
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

CPlantilla::CPlantilla(Var 1, Var 2)
:cTransform(nullptr)
{

}

CPlantilla::~CPlantilla() {

}

void CPlantilla::Init(){

    engine = Singleton<GameEngine>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

void CPlantilla::Update(){
    // UPDATE

}

void CPlantilla::FixedUpdate(){
    // UPDATE

}

gg::EMessageStatus CPlantilla::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}

gg::EMessageStatus CPlantilla::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}
