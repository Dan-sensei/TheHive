#ifndef SONIDO_IMPACTO_H
#define SONIDO_IMPACTO_H

#include "SoundEvent.hpp"

class SonidoImpacto : public SoundEvent {
    public:
        SonidoImpacto();
        void newSoundEvent(FMOD::Studio::EventInstance*);
        ~SonidoImpacto();
};

#endif