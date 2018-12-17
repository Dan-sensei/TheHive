#include "SoundEvent.hpp"

SoundEvent::SoundEvent(){}
SoundEvent::~SoundEvent(){}
 
void SoundEvent::play(){
	ERRCHECK(soundInstance->start());
	ERRCHECK(soundInstance->setVolume(1));
}
