#ifndef HABILITY3
#define HABILITY3

#include "Enumhabs.hpp"
#include <chrono>
#include <GameEngine/ScreenConsole.hpp>
#include "Hability.hpp"
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



};
#endif
