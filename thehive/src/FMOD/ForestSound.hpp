#ifndef FOREST_SOUND_H
#define FOREST_SOUND_H

#include "SoundEvent.hpp"

class ForestSound : public SoundEvent {
    public:
        ForestSound(FMOD::Studio::EventInstance*);
        ~ForestSound();
};

#endif
