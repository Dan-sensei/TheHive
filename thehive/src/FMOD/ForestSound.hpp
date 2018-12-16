#ifndef _FORESTSOUND_H
#define _FORESTSOUND_H

#include "SoundSystem.hpp"

class ForestSound : public SoundEvent {


public:

    ForestSound();
    ~ForestSound();

    SoundEvent* newSoundEvent(FMOD::Studio::EventInstance* ins);

    void setInstance(FMOD::Studio::EventInstance* ins);

};

#endif
