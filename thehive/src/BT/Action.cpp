#include "Action.hpp"
#include <iostream>


Action::Action(const Action &orig){
    Action(orig.tarea);
}
Action::Action(Hojas task){

    VectorAcciones[ANDAR_RAND] = &Action::andar_random;
    VectorAcciones[COMER] = &Action::comer_animal;
    VectorAcciones[GIRAR] = &Action::girar_enemigo;
    VectorAcciones[RANGO] = &Action::rango_visual;
    VectorAcciones[MOVER] = &Action::move_to;
    //VectorAcciones[10_METROS] = &Action::move_to;
    //VectorAcciones[3_ATACK] = &Action::move_to;
    //VectorAcciones[ON_RANGE] = &Action::move_to;
    //VectorAcciones[IN_PLACE] = &Action::move_to;
    //VectorAcciones[PLAYER_SEEN] = &Action::move_to;
    //VectorAcciones[PLAYER_SEEING] = &Action::move_to;
    //VectorAcciones[MOVE_AROUND] = &Action::move_to;
    //VectorAcciones[BLOCK] = &Action::move_to;
    //VectorAcciones[MOVE_TO_PLAYER] = &Action::move_to;
    //VectorAcciones[HIT] = &Action::move_to;
    //VectorAcciones[MOVE_TO_LAST_POS_KWON] = &Action::move_to;
    //VectorAcciones[JUST_MOVE] = &Action::move_to;

    tarea = task;

}

Action::~Action(){
    //VectorAcciones eliminar
}

void Action::onInitialize(){
    s = BH_INVALID;
}//parámetros del mundo necesarios para el update} // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Action::update() {

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
    setActive("andar random",0);
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


void Action::onTerminate(Status state){//tener cuidado de cerrar todos los recursos que abramos
  //std::cout << "hoja0 onTerminate" <<state << '\n';
}
