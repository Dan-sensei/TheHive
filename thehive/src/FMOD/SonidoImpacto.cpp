#include "SonidoImpacto.hpp"

SonidoImpacto::SonidoImpacto(){}

void SonidoImpacto::setImpacto(float impacto){

    soundInstance->setParameterValue("Impacto", impacto);

}

void SonidoImpacto::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    SoundEvent::soundInstance = _instance;
}


SonidoImpacto::~SonidoImpacto(){}
