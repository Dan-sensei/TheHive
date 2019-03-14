#include "SonidoNormal.hpp"

SonidoNormal::SonidoNormal(){}

void SonidoNormal::newSoundEvent(FMOD::Studio::EventInstance *_instance){
    SoundEvent::soundInstance = _instance;
}


SonidoNormal::~SonidoNormal(){}
