#ifndef HABILITY3
#define HABILITY3

#include "Enumhabs.hpp"
#include <chrono>
#include <Omicron/2D/Motor2D.hpp>
#include "Hability.hpp"
#include <FMOD/SoundSystem.hpp>
#include <FMOD/SonidoNormal.hpp>
//#include <string>

class CTriggerSystem;
class Hability3 : public Hability{

public:
    Hability3 (const Hability3 &orig);
    Hability3 (int _id);
    Hability3 ();
    virtual ~Hability3 ();

    virtual void Hab1_init ();

private:

    SoundSystem* SS;

    SoundEvent* s_hab;


};
#endif
