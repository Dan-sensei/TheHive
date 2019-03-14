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

void SoundEvent::stop_fadeout(){
	ERRCHECK(soundInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
}

void SoundEvent::pause(bool pause){
	ERRCHECK(soundInstance->setPaused(pause));
}

void SoundEvent::setPitch(float pitch){
	ERRCHECK(soundInstance->setPitch(pitch));
}

void SoundEvent::setVolume(float vol){
	ERRCHECK(soundInstance->setVolume(vol));
}

void SoundEvent::setPosition(glm::vec3 _pos){

	FMOD_3D_ATTRIBUTES *att;
	soundInstance->get3DAttributes(att);

	FMOD_VECTOR vec;
	vec.x = _pos.x;
	vec.y = _pos.y;
	vec.z = _pos.z;

	att->position = vec;
	soundInstance->set3DAttributes(att);

}

SoundEvent* SoundEvent::getEvent(){
	return this;
}

bool SoundEvent::isPlaying(){
	bool *ret;
	ERRCHECK(soundInstance->getPaused(ret));
	return &ret;
}
