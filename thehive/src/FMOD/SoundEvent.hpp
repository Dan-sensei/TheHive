#ifndef SOUND_EVENT_H
#define SOUND_EVENT_H

<<<<<<< HEAD
#include "inc/fmod_extra.hpp"
=======
#include <FMOD/fmod_extra.hpp>
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
#include <Util.hpp>

class SoundEvent {
    friend class SoundSystem;
    public:
<<<<<<< HEAD
        virtual ~SoundEvent();
        void play();

    protected:
        FMOD::Studio::EventInstance* soundInstance;
        SoundEvent();
=======
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
        bool isStop();

    protected:
        FMOD::Studio::EventInstance* soundInstance;
        virtual void newSoundEvent(FMOD::Studio::EventInstance*) = 0;
>>>>>>> 631f6232a2abeb04405aa707c4503ca6b4ed7cce
};
#endif
