#ifndef SOUND_EVENT_H
#define SOUND_EVENT_H

#include "inc/fmod_extra.hpp"
#include <Util.hpp>

class SoundEvent {
    friend class SoundSystem;
    public:
        virtual ~SoundEvent();
        void play();
        void stop();

    protected:
        FMOD::Studio::EventInstance* soundInstance;
        SoundEvent();
};
#endif
