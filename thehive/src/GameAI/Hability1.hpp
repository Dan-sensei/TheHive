#ifndef HABILITY1
#define HABILITY1

#include "Enumhabs.hpp"
#include <chrono>
#include <GameEngine/Motor2D.hpp>
#include "Hability.hpp"
//#include <string>

class CTriggerSystem;
class Hability1 : public Hability{

public:
    Hability1 (const Hability1 &orig);
    Hability1 (int _id);
    Hability1 ();
    virtual ~Hability1 ();

    virtual void Hab1_init ();

private:



};
#endif
