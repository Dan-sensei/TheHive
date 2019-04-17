#include "Hability2.hpp"
//#include "Enum.hpp"
#include <Omicron/2D/Motor2D.hpp>
#include <Singleton.hpp>
#include <ComponentArch/Components/CPlayerController.hpp>

//overload

    /* data */
    //void Hability::iniciar (Blackboard* _data){
    //    Hability (Blackboard* _data);

    //}
    Hability2::Hability2 (int _id):Hability(_id,4000,8000)
    {
        SS = Singleton<SoundSystem>::Instance();

        s_hab = new SonidoNormal();
        SS->createSound("event:/Voces/Jugador/FraseOverload", s_hab);

        s_hab2 = new SonidoNormal();
        SS->createSound("event:/SFX/Jugador/Habilidades/OverloadEnd", s_hab2);


    }
    Hability2::Hability2 (){

    }
    Hability2::~Hability2 (){
        delete s_hab;
        delete s_hab2;
    }

    Hability2::Hability2 (const Hability2 &orig){


    id=orig.id;
    duracion=orig.duracion;
    cooldown=orig.cooldown;
    nocool=orig.nocool;
    terminado=orig.terminado;
    nTimeStamp=orig.nTimeStamp;
    cTriggerSystem=orig.cTriggerSystem;




}


    //codigo de las habilidades
    void Hability2::Hab1_init (){
        //Manager = Singleton<ObjectManager>::Instance();
        CPlayerController* cPlayer = static_cast<CPlayerController*>(Singleton<ObjectManager>::Instance()->getComponent(gg::PLAYERCONTROLLER, id));
        cPlayer->SprintBuf();
        s_hab->play();
        //cPlayer->debuf();
    }
    void Hability2::Hab1_terminate(){

        CPlayerController* cPlayer = static_cast<CPlayerController*>(Singleton<ObjectManager>::Instance()->getComponent(gg::PLAYERCONTROLLER, id));
        cPlayer->SprintDebuf();
        s_hab2->play();
    }
