#include "Hability.hpp"
//#include "Enum.hpp"
#include <GameEngine/Motor2D.hpp>
#include <Singleton.hpp>

/* data */
//void Hability::iniciar (Blackboard* _data){
//    Hability (Blackboard* _data);

//}

Hability::Hability (int _id,float _duracion,int _cooldown)
: cTriggerSystem(nullptr),id(_id),duracion(_duracion),cooldown(_cooldown),terminado(true),nocool(true),prog(1)
{
    //nombres[NUM_HABS]="ojete";
    std::chrono::high_resolution_clock::time_point  begin = std::chrono::high_resolution_clock::now();
    nTimeStamp=std::chrono::high_resolution_clock::now();;//
}

Hability::Hability (){}
Hability::~Hability (){}

Hability::Hability (const Hability &orig){
    id=orig.id;
    duracion=orig.duracion;
    cooldown=orig.cooldown;
    nocool=orig.nocool;
    terminado=orig.terminado;
    nTimeStamp=orig.nTimeStamp;
    cTriggerSystem=orig.cTriggerSystem;
}

void Hability::init(){
    if(nocool){
        iniciar();
        Hab1_init ();
    }
}
void Hability::update (){
    if(!terminado){
        if(!terminar(duracion,terminado)){
            //update
            Hab1_update();
        }else{
            //terminate
            Hab1_terminate();
        }
    }
    else if(!nocool){
        terminar(cooldown,nocool);
    }
}


bool Hability::terminar(float _dur,bool& res){
    std::chrono::high_resolution_clock::time_point nCurTime = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(nCurTime - nTimeStamp).count();
    if(ms>_dur){
        res= true;
    }
    prog=(float)ms/cooldown;
    if (prog>=1){
        prog=1;
    }
    //Singleton<Motor2D>::Instance()->setprogress(tipo,prog);
    return res;
}

void Hability::iniciar(){
    prog=0;
    terminado=false;
    nocool=false;
    std::chrono::high_resolution_clock::time_point  begin = std::chrono::high_resolution_clock::now();
    nTimeStamp=std::chrono::high_resolution_clock::now();//
}

float Hability::getProg(){
    return prog;
}


    //codigo de las habilidades
    void Hability::Hab1_init (){

    }
    void Hability::Hab1_update(){


    }
    void Hability::Hab1_terminate(){


    }
