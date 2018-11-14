#include "CPlantilla.hpp"
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager


#define MAX_ANGLE 12.f

#define DASH_KEY gg::GG_ALT
#define ROTATE_KEY gg::GG_LCONTROL
#define RUN_KEY gg::GG_LSHIFT

CPlantilla::CPlantilla()
:cTransform(nullptr)
{

}

CPlantilla::~CPlantilla() {

}

void CPlantilla::initComponent() {
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto

    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_SETPTRS);

}

void CPlantilla::initializeComponentData(const void* data){

    if(data){
        InitPlantilla* cData = (InitPlantilla*)data;
        // Si le pasamos cosas, convertimos el void* a la estructura inicializadora para acceder a los elementos
        cData->valor1;
        ...
    }
    engine = Singleton<GameEngine>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}


gg::EMessageStatus CPlantilla::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CPlantilla::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CPlantilla::MHandler_UPDATE(){
    // UPDATE
    return gg::ST_TRUE;
}
