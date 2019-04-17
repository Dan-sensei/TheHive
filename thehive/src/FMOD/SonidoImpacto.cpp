#include "SonidoImpacto.hpp"

SonidoImpacto::SonidoImpacto(){}


void SonidoImpacto::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    soundInstance = _instance;
}


SonidoImpacto::~SonidoImpacto(){
    soundInstance->release();
}
