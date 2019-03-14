#include "SonidoEscopeta.hpp"

SonidoEscopeta::SonidoEscopeta(){}

void SonidoEscopeta::setCargador(float lleno){

    soundInstance->setParameterValue("Lleno", lleno);

}

void SonidoEscopeta::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    SoundEvent::soundInstance = _instance;
}

SonidoEscopeta::~SonidoEscopeta(){}
