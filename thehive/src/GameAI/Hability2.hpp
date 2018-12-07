#ifndef HABILITY2
#define HABILITY2

#include "Hability.hpp"
//#include <string>

class CTriggerSystem;
class Hability2 : public Hability{

public:
    Hability2 (const Hability2 &orig);
    Hability2 (int _id);
    Hability2 ();
    virtual ~Hability2 ();

    virtual void Hab1_init ();
    virtual void Hab1_terminate();

private:



};
#endif
