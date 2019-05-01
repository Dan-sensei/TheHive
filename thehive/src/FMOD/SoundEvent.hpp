#ifndef SOUND_EVENT_H
#define SOUND_EVENT_H

#include <FMOD/fmod_extra.hpp>
#include <FMOD/fmod_studio_common.h>
#include <FMOD/fmod_studio.h>

#include <Util.hpp>

class SoundEvent {
    friend class SoundSystem;
    public:
        SoundEvent();
        virtual ~SoundEvent()=0;
        void play();
        void setParameter(const std::string&, float);
        void stop();
        void stop_fadeout();
        void pause(bool);
        void setPitch(float);
        void setVolume(float);
        void setPosition(glm::vec3);
        SoundEvent* getEvent();
        bool isPlaying();

    protected:
        FMOD_STUDIO_EVENTINSTANCE* soundInstance;
        virtual void newSoundEvent(FMOD_STUDIO_EVENTINSTANCE*) = 0;
};
#endif
