#include "CClock.hpp"
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager

CClock::CClock()
{
    limitReached = false;
    initialized = false;
    msEnd = -1;
}

CClock::~CClock(){}

void CClock::initComponent(){
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto

    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::CLOCK, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::CLOCK, gg::M_SETPTRS);

}

void CClock::Init(){
    engine = Singleton<GameEngine>::Instance();

    //  Inicializar punteros a otras compnentes
    MHandler_SETPTRS();
}

bool CClock::startChrono(float _end){
    if(initialized){
        return false;
    }
    else{
        // gg::cout("INIT CHRONO ON "+std::to_string(_end));
        limitReached = false;
        initialized = true;
        msEnd       = _end;
        begin       = std::chrono::high_resolution_clock::now();
        return true;
    }
}

bool CClock::setEndTime(float _end){
    if(!initialized){
        return false;
    }
    else{
        msEnd = _end;
        return true;
    }
}

float CClock::getActualTime(){
    if(!initialized){
        return -1;
    }
    else{
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsedtime = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count();
        return ms;
    }
}

bool CClock::hasEnded(){
    if(!initialized)    return false;
    else{
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsedtime = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsedtime).count();
        if(ms > msEnd){
            initialized = false;
            limitReached = true;
            return true;
        }
        else            return false;
    }
}

gg::EMessageStatus CClock::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CClock::MHandler_SETPTRS(){
    // Inicializando punteros

    return gg::ST_TRUE;
}

gg::EMessageStatus CClock::MHandler_UPDATE(){
    // UPDATE
    return gg::ST_TRUE;
}
