#include "SonidoSuperficie.hpp"

SonidoSuperficie::SonidoSuperficie(){}

void SonidoSuperficie::setSuperficie(float superficie){

    soundInstance->setParameterValue("Superficie",superficie);

}

void SonidoSuperficie::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    soundInstance = _instance;
}

SonidoSuperficie::~SonidoSuperficie(){
    soundInstance->release();
}
