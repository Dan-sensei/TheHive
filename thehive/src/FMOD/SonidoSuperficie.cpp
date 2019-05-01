#include "SonidoSuperficie.hpp"

SonidoSuperficie::SonidoSuperficie(){}

void SonidoSuperficie::newSoundEvent(FMOD_STUDIO_EVENTINSTANCE *_instance){
    soundInstance = _instance;
}

SonidoSuperficie::~SonidoSuperficie(){
    // soundInstance->release();
    FMOD_Studio_EventInstance_Release(soundInstance);
}
