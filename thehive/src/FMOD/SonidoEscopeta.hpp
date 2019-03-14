#ifndef SONIDO_ESCOPETA_H
#define SONIDO_ESCOPETA_H

#include "SoundEvent.hpp"


class SonidoEscopeta : public SoundEvent {
    public:
        SonidoEscopeta();
        void setCargador(float);
        void newSoundEvent(FMOD::Studio::EventInstance*);
        ~SonidoEscopeta();
};

#endif
