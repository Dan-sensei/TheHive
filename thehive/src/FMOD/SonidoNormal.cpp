#include "SonidoNormal.hpp"

SonidoNormal::SonidoNormal(){}

void SonidoNormal::newSoundEvent(FMOD_STUDIO_EVENTINSTANCE *_instance){
    soundInstance = _instance;
}


SonidoNormal::~SonidoNormal(){
    // ERRCHECK(soundInstance->release());
    FMOD_Studio_EventInstance_Release(soundInstance);
}
