#include "Hability.hpp"
//#include "Enum.hpp"
#include <GameEngine/ScreenConsole.hpp>
#include <Singleton.hpp>



    /* data */
    //void Hability::iniciar (Blackboard* _data){
    //    Hability (Blackboard* _data);

    //}
    Hability::Hability (int _id,EHabType _tipo,float _duracion,int _cooldown)
    : cTriggerSystem(nullptr),id(_id),tipo(_tipo),duracion(_duracion),cooldown(_cooldown),terminado(true),nocool(true)
    {
        VectorAccionesInit[HAB1] = &Hability::Hab1_init;
        VectorAccionesUpdate[HAB1] = &Hability::Hab1_update;
        VectorAccionesTerminate[HAB1] = &Hability::Hab1_terminate;
        //nombres[NUM_HABS]="ojete";

        std::chrono::high_resolution_clock::time_point  begin = std::chrono::high_resolution_clock::now();
        nTimeStamp=std::chrono::high_resolution_clock::now();;//

    }
    Hability::Hability (){

    }
    Hability::~Hability (){
    }
    void Hability::init(){
        //std::cout << "init" << '\n';
        //id(_id),tipo(_tipo),duracion(_duracion),cooldown(_cooldown),terminado(true)
        //std::cout << "id:"              <<id<< '\n';
        //std::cout << "tipo:"            <<tipo<< '\n';
        //std::cout << "duracion:"        <<duracion<< '\n';
        //std::cout << "cooldown:"        <<cooldown<< '\n';
        //std::cout << "terminado:"       <<terminado<< '\n';
        //std::cout << "nocool:"          <<nocool<< '\n';

        if(nocool){
            iniciar();
            if(VectorAccionesInit[tipo] != nullptr)
                (this->*VectorAccionesInit[tipo])();
        }

    }
    void Hability::update (){
        if(!terminado){
            if(!terminar(duracion,terminado)){
                //update
                //std::cout << "update" << '\n';
                if(VectorAccionesUpdate[tipo] != nullptr)
                    (this->*VectorAccionesUpdate[tipo])();
            }else{
                //terminate
                //std::cout << "terminate" << '\n';
                if(VectorAccionesTerminate[tipo] != nullptr)
                    (this->*VectorAccionesTerminate[tipo])();
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
        float prog=(float)ms/cooldown;
        if (prog>=1){
            prog=1;
        }
        Singleton<ScreenConsole>::Instance()->setprogress(prog);
        return res;
    }
    void Hability::iniciar(){
        terminado=false;
        nocool=false;
        std::chrono::high_resolution_clock::time_point  begin = std::chrono::high_resolution_clock::now();
        nTimeStamp=std::chrono::high_resolution_clock::now();//
    }



    //codigo de las habilidades
    void Hability::Hab1_init (){

    }
    void Hability::Hab1_update(){
        //std::cout << "update" << '\n';


    }
    void Hability::Hab1_terminate(){
        //std::cout << "update" << '\n';


    }
