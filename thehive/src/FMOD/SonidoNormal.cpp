#include "SonidoNormal.hpp"

SonidoNormal::SonidoNormal(){}

void SonidoNormal::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    soundInstance = _instance;
}


SonidoNormal::~SonidoNormal(){
    ERRCHECK(soundInstance->release());
}
