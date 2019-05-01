#include "SonidoSalud.hpp"

SonidoSalud::SonidoSalud(){}


void SonidoSalud::newSoundEvent(FMOD_STUDIO_EVENTINSTANCE *_instance){
    soundInstance = _instance;
}


SonidoSalud::~SonidoSalud(){
    // soundInstance->release();
    FMOD_Studio_EventInstance_Release(soundInstance);
}
