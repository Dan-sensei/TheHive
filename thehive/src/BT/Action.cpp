#include "Action.hpp"
#include <iostream>
#include <ComponentArch/Components/CTransform.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <Util.hpp>
#include <string>
#include <random>
#include "EventSystem/BVector3f.hpp"


//#include <Util>
/*
data
float agresividad;
gg::Vector3f playerPos;
bool playerSeen;
bool playerSeeing;

gg::Vector3f playerPos;
gg::Vector3f destino;



float range;
Blackboard* data;
bool playerOnRange;
float enfado;
BehaviorTree* BT;





*/


Action::Action(const Action &orig){
    Action(orig.tarea,orig.data);
}
Action::Action(Hojas task,Blackboard* _data){

    VectorAcciones[ANDAR_RAND] = &Action::andar_random;
    VectorAcciones[COMER] = &Action::comer_animal;
    VectorAcciones[GIRAR] = &Action::girar_enemigo;
    VectorAcciones[RANGO] = &Action::rango_visual;
    VectorAcciones[MOVER] = &Action::move_to;
    ///
    VectorAcciones[TEN_METROS] = &Action::distancia10;//si
    VectorAcciones[THREE_ATACK] = &Action::move_to;//ni idea si
    VectorAcciones[ON_RANGE] = &Action::onrange;//si
    VectorAcciones[IN_PLACE] = &Action::move_to;//inutilidad maxima si
    VectorAcciones[PLAYER_SEEN] = &Action::seen;//si
    VectorAcciones[PLAYER_SEEING] = &Action::seeing;//si
    VectorAcciones[MOVE_AROUND] = &Action::move_around;//si
    VectorAcciones[BLOCK] = &Action::move_around;//trucada
    VectorAcciones[MOVE_TO_PLAYER] = &Action::move_player;//si
    VectorAcciones[HIT] = &Action::move_to;//ni idea si
    VectorAcciones[MOVE_TO_LAST_POS_KWON] = &Action::move_last;//si
    VectorAcciones[JUST_MOVE] = &Action::move_around;//trucada

    data=_data;
    tarea = task;

}

Action::~Action(){
    //VectorAcciones eliminar
}

void Action::onInitialize(){
    //std::cout << "Accion onInitialize" << '\n';
    s = BH_INVALID;
}//parámetros del mundo necesarios para el update} // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Action::update() {
    //std::cout << "Accion Update" <<tarea<< '\n';

    if(VectorAcciones[tarea] != nullptr)
        (this->*VectorAcciones[tarea])();

    return s;

}// Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Action::setActive(std::string a, bool acierto){
    //std::cout<< a << " update" <<getStatus() << '\n';

    if(acierto)
        s = BH_SUCCESS;
    else
        s = BH_FAILURE;

}

void Action::andar_random(){
    //std::cout << "andar_random" << '\n';
    setActive("andar random",0);

}
void Action::distancia10(){//int tipo){
    //std::cout << "distancia10" << '\n';

    //std::cout << "se hace wey" << '\n';
    distancia(10);//int tipo){


}
void Action::checkbool(std::string that){
    if(data->getBData(that)->getBool()){
        s=BH_SUCCESS;
    }else{
        s=BH_FAILURE;
    }
}
void Action::onrange(){
    //std::cout << "range" << '\n';

    checkbool("playerOnRange");
}
void Action::seeing(){
    //std::cout << "seeing" << '\n';

    //std::cout << "primerito" << '\n';
    checkbool("playerSeeing");
}
void Action::seen(){
    //std::cout << "seen" << '\n';

    checkbool("playerSeen");
}


void Action::distancia(float _dist){//int tipo){

    //setActive("andar random",0);
    //data->getBData("playerPos")->getVector3f();

    //CAIEnem* enem=static_cast<CAIEnem*>(Singleton<ObjectManager>::Instance()->getComponent(gg::AIENEM,getEntityID()));
    //enem->enemyseen(_pRec);

    CTransform* cTransform;     //  Punteros a otras componentes
    float id=data->getBData("id")->getInt();
    //std::cout << "id" <<id<< '\n';
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,id));
    gg::Vector3f mio =cTransform->getPosition();
    //std::cout << "aqui peta" << '\n';
    gg::Vector3f dest =data->getBData("playerPos")->getVector3f();
    //std::cout << "aqui peta" << '\n';

    float dist=gg::DIST(mio,dest);
    //std::cout << "aqui peta" << '\n';
    if(dist<_dist){
        s=BH_SUCCESS;

    }else{
        s=BH_FAILURE;

    }
    //data->getBData("dist");

}
void Action::comer_animal(){
    setActive("comer",1);
}
void Action::girar_enemigo(){
    setActive("girar",1);
}
void Action::rango_visual(){
    setActive("rango",1);
}
void Action::move_to(){
    setActive("mover",1);
}
void Action::move_last(){
    //std::cout << "move last" << '\n';

    if(s!=BH_RUNNING){
        data->setData("destino",new BVector3f(data->getBData("playerPos")->getVector3f()));
    }
    move_too();
}
void Action::move_player(){
    //std::co << "move player" << '\n';

    //if(s!=BH_RUNNING){
        data->setData("destino",new BVector3f(data->getBData("playerPos")->getVector3f()));
    //}
    move_too();
}

void Action::move_around(){
    //std::cout << "move around" << '\n';
    if(s!=BH_RUNNING){
        //elegir
        //std::cout << "elegimos" << '\n';
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<int> distribution(-50,50);
        int x = distribution(gen);
        int y = distribution(gen);
        //std::cout << "X:" <<x<< '\n';
        //std::cout << "Y" <<y<< '\n';
        CTransform* cTransform;     //  Punteros a otras componentes
        cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,data->getBData("id")->getInt()));
        //gg::Vector3f dest =data->getBData("destino")->getVector3f();
        gg::Vector3f mio =cTransform->getPosition();
        //std::cout << "mio:" <<mio << '\n';
        gg::Vector3f dest =mio+gg::Vector3f(x,0,y);
        //std::cout << "dest:" <<dest << '\n';
        //cTransform->setPosition(mio);
        data->setData("destino",new BVector3f(dest));

    }
    move_too();
}

void Action::move_too(){
    CTransform* cTransform;     //  Punteros a otras componentes
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,data->getBData("id")->getInt()));
    gg::Vector3f mio =cTransform->getPosition();
    //std::cout << "mio" <<mio<< '\n';

    gg::Vector3f dest =data->getBData("destino")->getVector3f();
    //std::cout << "dest" <<dest<< '\n';
    //gg::Normalice(dest-mio)*2;
    cTransform->setPosition(mio+gg::Normalice(dest-mio)*1/15);
    float dist=gg::DIST(mio,dest);
    //std::cout << "dist" <<dist<< '\n';
    if(dist<5){
        s=BH_SUCCESS;
    }else{
        s=BH_RUNNING;
    }

}
void Action::onTerminate(Status state){//tener cuidado de cerrar todos los recursos que abramos
  //std::cout << "Accion onTerminate" <<state << '\n';
}
