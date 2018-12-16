#include "ForestSound.hpp"

ForestSound::ForestSound():SoundEvent(){};


ForestSound::~ForestSound(){

}


SoundEvent* ForestSound::newSoundEvent(FMOD::Studio::EventInstance* ins){

    ForestSound* sound = new ForestSound();
    sound->setInstance(ins);
    //soundInstance=ins;

    return sound;
}

void ForestSound::setInstance(FMOD::Studio::EventInstance* ins){
    soundInstance=ins;
}
