#include "SonidoEscopeta.hpp"

SonidoEscopeta::SonidoEscopeta(){}

void SonidoEscopeta::newSoundEvent(FMOD_STUDIO_EVENTINSTANCE *_instance){
    soundInstance = _instance;
}

SonidoEscopeta::~SonidoEscopeta(){
    // soundInstance->release();
    FMOD_Studio_EventInstance_Release(soundInstance);
    
}
