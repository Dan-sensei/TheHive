#include "SonidoSalud.hpp"

SonidoSalud::SonidoSalud(){}

void SonidoSalud::setVida(float vida){

    soundInstance->setParameterValue("Vida", vida);

}

void SonidoSalud::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    SoundEvent::soundInstance = _instance;
}


SonidoSalud::~SonidoSalud(){}
