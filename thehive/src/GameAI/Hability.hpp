#ifndef HABILITY
#define HABILITY

#include "Enumhabs.hpp"
#include <chrono>
#include <GameEngine/ScreenConsole.hpp>
//#include <string>

class CTriggerSystem;
class Hability {
public:
    Hability (const Hability &orig);
    Hability (int _id,float _duracion,int _cooldown);
    Hability ();
    virtual ~Hability ();
    void init();
    void update();
    void iniciar();
    bool terminar(float _dur,bool& res);

    virtual void Hab1_init ();
    virtual void Hab1_update ();
    virtual void Hab1_terminate ();
    float getProg();

protected:
    /* data */
    //EHabType tipo;
    int id;
    float duracion;
    int cooldown;
    bool nocool;
    bool terminado;
    std::chrono::high_resolution_clock::time_point nTimeStamp;


    //string nombres[NUM_HABS];


    CTriggerSystem* cTriggerSystem;
    float prog;



};
#endif
