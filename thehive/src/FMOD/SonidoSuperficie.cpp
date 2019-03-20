#include "SonidoSuperficie.hpp"

SonidoSuperficie::SonidoSuperficie(){}

void SonidoSuperficie::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    soundInstance = _instance;
}

SonidoSuperficie::~SonidoSuperficie(){
    soundInstance->release();
}
