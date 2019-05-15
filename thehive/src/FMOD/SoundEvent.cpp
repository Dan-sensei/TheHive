#include "SoundEvent.hpp"

SoundEvent::SoundEvent(){}
SoundEvent::~SoundEvent(){}

void SoundEvent::play(){
	// ERRCHECK(soundInstance->start());
	// ERRCHECK(soundInstance->setVolume(1));
	FMOD_Studio_EventInstance_Start(soundInstance);
	FMOD_Studio_EventInstance_SetVolume(soundInstance,1);
}

void SoundEvent::setParameter(const std::string& parameter, float valor){
    // soundInstance->setParameterValue(parameter.c_str(), valor);
	FMOD_Studio_EventInstance_SetParameterValue(soundInstance,parameter.c_str(), valor);
}

void SoundEvent::stop(){
	// ERRCHECK(soundInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE));
	FMOD_Studio_EventInstance_Stop(soundInstance,FMOD_STUDIO_STOP_IMMEDIATE);
}

void SoundEvent::stop_fadeout(){
	// ERRCHECK(soundInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
	FMOD_Studio_EventInstance_Stop(soundInstance,FMOD_STUDIO_STOP_ALLOWFADEOUT);
}

void SoundEvent::pause(bool pause){
	// ERRCHECK(soundInstance->setPaused(pause));
	FMOD_Studio_EventInstance_SetPaused(soundInstance,pause);
}

void SoundEvent::setPitch(float pitch){
	// ERRCHECK(soundInstance->setPitch(pitch));
	FMOD_Studio_EventInstance_SetPitch(soundInstance,pitch);
}

void SoundEvent::setVolume(float vol){
	// ERRCHECK(soundInstance->setVolume(vol));
	FMOD_Studio_EventInstance_SetVolume(soundInstance,vol);
}

void SoundEvent::setPosition(glm::vec3 _pos){

	FMOD_3D_ATTRIBUTES *att;
	// soundInstance->get3DAttributes(att);
	FMOD_Studio_EventInstance_Get3DAttributes(soundInstance,att);

	FMOD_VECTOR vec;
	vec.x = _pos.x;
	vec.y = _pos.y;
	vec.z = _pos.z;

	att->position = vec;
	// soundInstance->set3DAttributes(att);
	FMOD_Studio_EventInstance_Set3DAttributes(soundInstance,att);

}

SoundEvent* SoundEvent::getEvent(){
	return this;
}

bool SoundEvent::isPaused(){
	FMOD_BOOL paused = false;
	bool ret = false;

	// soundInstance->getPaused(&paused);
	FMOD_Studio_EventInstance_GetPaused(soundInstance,&paused);

	if(!paused)
			ret = true;


	return ret;
}


bool SoundEvent::isPlaying(){
	FMOD_STUDIO_PLAYBACK_STATE state = FMOD_STUDIO_PLAYBACK_PLAYING;
	bool ret = false;

	// soundInstance->getPaused(&paused);
	FMOD_Studio_EventInstance_GetPlaybackState(soundInstance,&state);


	if(state == FMOD_STUDIO_PLAYBACK_PLAYING)
			ret = true;


	return ret;
}
