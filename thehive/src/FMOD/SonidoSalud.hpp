#ifndef SONIDO_SALUD_H
#define SONIDO_SALUD_H

#include "SoundEvent.hpp"

class SonidoSalud : public SoundEvent{
    public:
        SonidoSalud();
        void newSoundEvent(FMOD_STUDIO_EVENTINSTANCE*);
        ~SonidoSalud();
};

#endif
