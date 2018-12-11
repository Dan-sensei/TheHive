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

void CClock::Init(){
    engine = Singleton<GameEngine>::Instance();
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
