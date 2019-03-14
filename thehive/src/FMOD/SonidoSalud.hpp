#ifndef SONIDO_SALUD_H
#define SONIDO_SALUD_H

#include "SoundEvent.hpp"

class SonidoSalud : public SoundEvent{
    public:
        SonidoSalud();
        void setVida(float);
        void newSoundEvent(FMOD::Studio::EventInstance*);
        ~SonidoSalud();
};

#endif
