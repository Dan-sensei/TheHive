#ifndef SONIDO_IMPACTO_H
#define SONIDO_IMPACTO_H

#include "SoundEvent.hpp"

class SonidoImpacto : public SoundEvent {
    public:
        SonidoImpacto();
        void newSoundEvent(FMOD_STUDIO_EVENTINSTANCE*);
        ~SonidoImpacto();
};

#endif
