#include "SonidoImpacto.hpp"

SonidoImpacto::SonidoImpacto(){}


void SonidoImpacto::newSoundEvent(FMOD_STUDIO_EVENTINSTANCE *_instance){
    soundInstance = _instance;
}


SonidoImpacto::~SonidoImpacto(){
    // soundInstance->release();
    FMOD_Studio_EventInstance_Release(soundInstance);
}
