#include "SonidoSalud.hpp"

SonidoSalud::SonidoSalud(){}

void SonidoSalud::setVida(float vida){

    soundInstance->setParameterValue("Vida", vida);

}

void SonidoSalud::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    soundInstance = _instance;
}


SonidoSalud::~SonidoSalud(){
    soundInstance->release();
}
