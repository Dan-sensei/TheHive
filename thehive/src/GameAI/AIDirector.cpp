#include "AIDirector.hpp"
//#include "Enum.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include <Singleton.hpp>
#include <Factory.hpp>

/* data */
//void AIDirector::iniciar (Blackboard* _data){
//    AIDirector (Blackboard* _data);

//}
#define MIN_WAN 4.f
#define MAX_WAN 10.f

AIDirector::AIDirector (int _id,float _duracion,int _cooldown)
: Manager(nullptr),fac(nullptr)
{
    Manager = Singleton<ObjectManager>::Instance();
    fac = Singleton<Factory>::Instance();

    //std::chrono::high_resolution_clock::time_point  begin = std::chrono::high_resolution_clock::now();
    //nTimeStamp=std::chrono::high_resolution_clock::now();;//

    /*
    cargar los puntos de  spawn del mapa
    */
}
void AIDirector::clean(){
    activado=false;
    numEnemigos=0;

}
void AIDirector::init(){
    activado=true;
    numEnemigos=0;
    enemigos.clear();

}

AIDirector::AIDirector (){}
AIDirector::~AIDirector (){}

AIDirector::AIDirector (const AIDirector &orig){
}

void AIDirector::update (){
    if(activado){

    }
}
void AIDirector::setActive(bool dato){
    activado=dato;
}
void AIDirector::subida(){

}
void AIDirector::pico(){

}
void AIDirector::bajada(){

}
void AIDirector::createWandering(gg::Vector3f posicion,float rango){
    int enemigos = gg::genIntRandom(MIN_WAN, MAX_WAN);
    for (int i = 0; i < enemigos; i++) {
        gg::Vector3f deltapos(gg::genIntRandom(-rango, rango),gg::genIntRandom(-rango, rango));
        //ver porque falla esto
        //enemigos.push_back(fac->createSoldierWandering(posicion+deltapos, 2000));
        numEnemigos++;
    }

}
void AIDirector::createHorda(gg::Vector3f posicion,float rango){
    CTransform* heropos=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, Manager->getHeroID()));
    gg::Vector3f dest=heropos->getPosition();
    int enemigos = gg::genIntRandom(MIN_WAN, MAX_WAN);
    for (int i = 0; i < enemigos; i++) {
        gg::Vector3f deltapos(gg::genIntRandom(-rango, rango),gg::genIntRandom(-rango, rango));
        //ver porque falla esto
        //CTransform
        int id=fac->createSoldierHorda(posicion+deltapos, 2000,dest);
        CTransform* enemypos=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id));
        //enemigos.push_back(enemypos);
        numEnemigos++;
    }

}
/*
jefe dejamos de invocar
*/
