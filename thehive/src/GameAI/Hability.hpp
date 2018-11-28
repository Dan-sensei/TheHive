#ifndef HABILITY
#define HABILITY

#include "Enumhabs.hpp"
#include <chrono>
#include <GameEngine/ScreenConsole.hpp>
//#include <string>

class CTriggerSystem;
class Hability {
private:
    /* data */
    EHabType tipo;
    int id;
    float duracion;
    int cooldown;
    bool nocool;
    bool terminado;
    std::chrono::high_resolution_clock::time_point nTimeStamp;


    using pFunc = void(Hability::*)();
    pFunc VectorAccionesInit[NUM_HABS];
    pFunc VectorAccionesUpdate[NUM_HABS];
    pFunc VectorAccionesTerminate[NUM_HABS];
    //string nombres[NUM_HABS];


    CTriggerSystem* cTriggerSystem;
public:
    Hability (int _id,EHabType _tipo,float _duracion,int _cooldown);
    Hability ();
    virtual ~Hability ();
    void init();
    void update();
    void iniciar();
    bool terminar(float _dur,bool& res);

    void Hab1_init ();
    void Hab1_update ();
    void Hab1_terminate ();




};
#endif
