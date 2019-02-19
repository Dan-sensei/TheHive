#include "SoundEvent.hpp"

SoundEvent::SoundEvent(){}
SoundEvent::~SoundEvent(){}

void SoundEvent::play(){
	ERRCHECK(soundInstance->start());
	ERRCHECK(soundInstance->setVolume(1));
}

void SoundEvent::stop(){
	ERRCHECK(soundInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}
