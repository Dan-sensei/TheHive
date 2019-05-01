#ifndef SONIDO_ESCOPETA_H
#define SONIDO_ESCOPETA_H

#include "SoundEvent.hpp"

class SonidoEscopeta : public SoundEvent {
    public:
        SonidoEscopeta();
        void newSoundEvent(FMOD_STUDIO_EVENTINSTANCE*);
        ~SonidoEscopeta();
};

#endif
