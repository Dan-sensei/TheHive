#ifndef SONIDO_NORMAL_H
#define SONIDO_NORMAL_H

#include "SoundEvent.hpp"

class SonidoNormal : public SoundEvent {
    public:
        SonidoNormal();
        void newSoundEvent(FMOD_STUDIO_EVENTINSTANCE*);
        ~SonidoNormal();
};

#endif
