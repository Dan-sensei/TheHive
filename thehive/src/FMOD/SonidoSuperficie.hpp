#ifndef SONIDO_SUPERFICIE_H
#define SONIDO_SUPERFICIE_H

#include "SoundEvent.hpp"

class SonidoSuperficie : public SoundEvent {
    public:
        SonidoSuperficie();
        void newSoundEvent(FMOD_STUDIO_EVENTINSTANCE*);
        ~SonidoSuperficie();
};

#endif
