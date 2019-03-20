#include "SonidoEscopeta.hpp"

SonidoEscopeta::SonidoEscopeta(){}

void SonidoEscopeta::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    soundInstance = _instance;
}

SonidoEscopeta::~SonidoEscopeta(){
    soundInstance->release();
}
