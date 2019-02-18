#include "ForestSound.hpp"

ForestSound::ForestSound(FMOD::Studio::EventInstance *_instance)
{
    SoundEvent::soundInstance = _instance;
}

ForestSound::~ForestSound(){}
