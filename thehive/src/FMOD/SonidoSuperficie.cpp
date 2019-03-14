#include "SonidoSuperficie.hpp"

SonidoSuperficie::SonidoSuperficie(){}

void SonidoSuperficie::setSuperficie(float superficie){

    soundInstance->setParameterValue("Superficie",superficie);

}

void SonidoSuperficie::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    SoundEvent::soundInstance = _instance;
}

SonidoSuperficie::~SonidoSuperficie(){}
