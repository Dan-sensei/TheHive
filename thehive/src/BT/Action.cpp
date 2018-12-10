#include "Action.hpp"
#include <iostream>
#include <ComponentArch/Components/CTransform.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <Util.hpp>
#include <string>
#include <random>
#include "EventSystem/BVector3f.hpp"
#include "EventSystem/BInt.hpp"
#include "EventSystem/BBool.hpp"
//#include "GameEngine/ScreenConsole.hpp"

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
    Action(orig.tarea,orig.data,orig.yo);
}
Action::Action(Hojas task,Blackboard* _data,CAIEnem* ai){
yo=ai;
    VectorAcciones[ANDAR_RAND] = &Action::andar_random;
    VectorAcciones[COMER] = &Action::comer_animal;
    VectorAcciones[GIRAR] = &Action::girar_enemigo;
    VectorAcciones[RANGO] = &Action::rango_visual;
    VectorAcciones[MOVER] = &Action::move_to;
    ///
    VectorAcciones[TEN_METROS] = &Action::distancia10;//si
    VectorAcciones[THREE_ATACK] = &Action::move_to;//ni idea si
    VectorAcciones[IN_PLACE] = &Action::move_to;//inutilidad maxima si
    VectorAcciones[BLOCK] = &Action::move_around;//trucada
    VectorAcciones[JUST_MOVE] = &Action::move_around;//trucada

    VectorAcciones[RANGO_ULTRASONIDO] = &Action::ultrasonido;//si
    VectorAcciones[ATURDIDO] = &Action::ult_cont;//si
    VectorAcciones[RANGO_SENYUELO] = &Action::senyuelo;//si
    VectorAcciones[MOVER_SENYUELO] = &Action::move_senyuelo;//si
    VectorAcciones[RONDAR_SENYUELO] = &Action::rond_seny;//TRUCADA
    VectorAcciones[PLAYER_SEEING] = &Action::seeing;//si
    VectorAcciones[ON_RANGE] = &Action::onrange;//si
    VectorAcciones[HIT] = &Action::comer_animal;//TRUCADA
    VectorAcciones[NOT_ATTACKED] = &Action::girar_enemigo;//TRUCADA
    VectorAcciones[ALLY_DEAD] = &Action::girar_enemigo;//TRUCADA
    VectorAcciones[MORE_RAGE] = &Action::comer_animal;//TRUCADA
    VectorAcciones[X_ALIENS_ATTACKING] = &Action::girar_enemigo;//TRUCADA
    VectorAcciones[X_METRES_PLAYER] = &Action::distancia10;//SI
    VectorAcciones[RONDAR_PLAYER] = &Action::rond_jugador;//TRUCADA
    VectorAcciones[PAUSE] = &Action::comer_animal;//TRUCADA
    VectorAcciones[MOVE_TO_PLAYER] = &Action::move_player;//si
    VectorAcciones[PLAYER_SEEN] = &Action::seen;//si
    VectorAcciones[MOVE_AROUND] = &Action::move_around;//siRANDOM
    VectorAcciones[MOVE_TO_LAST_POS_KWON] = &Action::move_last;//si
    VectorAcciones[IN_LAST_POS_KWON] = &Action::in_last;//si

    data=_data;
    tarea = task;

}

Action::~Action(){
    //VectorAcciones eliminar
}

void Action::onInitialize(){
    //// std::cout << "Accion onInitialize" << '\n';
    s = BH_INVALID;
}//parámetros del mundo necesarios para el update} // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Action::update() {
    //// std::cout << "Accion Update" <<tarea<< '\n';
    //gg::cout("action nº"+std::to_string(tarea));

    if(VectorAcciones[tarea] != nullptr)
        (this->*VectorAcciones[tarea])();

    return s;

}// Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Action::setActive(std::string a, bool acierto){
    //// std::cout<< a << " update" <<getStatus() << '\n';

    if(acierto)
        s = BH_SUCCESS;
    else
        s = BH_FAILURE;

}

void Action::andar_random(){
    //// std::cout << "andar_random" << '\n';
    setActive("andar random",0);

}
void Action::distancia10(){//int tipo){
    //// std::cout << "distancia10" << '\n';

    //// std::cout << "se hace wey" << '\n';
    distancia(10,yo->playerPos);//int tipo){


}
void Action::in_last(){//int tipo){
    //// std::cout << "distancia10" << '\n';

    //// std::cout << "se hace wey" << '\n';
    distancia(0.5,yo->playerPos);//int tipo){
if(s==BH_SUCCESS){
    s=BH_FAILURE;
}else{
    s=BH_SUCCESS;
}

}
void Action::checkbool(bool that){
    if(that){
        s=BH_SUCCESS;
        //// std::cout << "cierto" << '\n';
    }else{
        s=BH_FAILURE;
    }
}
void Action::onrange(){
    //// std::cout << "range" << '\n';

    checkbool(yo->playerOnRange);

}
void Action::seeing(){
    //// std::cout << "viendo?" << '\n';
    checkbool(yo->playerSeeing);

}
void Action::ultrasonido(){
    checkbool(yo->ultrasonido);
}
void Action::senyuelo(){
    checkbool(yo->senyuelo);

}

void Action::seen(){
    checkbool(yo->playerSeen);

}
void Action::rond_seny(){
    if(s!=BH_RUNNING){
        // std::cout << "iniciando rondando senyuelo" << '\n';
        yo->destino=yo->senpos;

    }

    rond();

}
void Action::rond_jugador(){
    if(s!=BH_RUNNING){
        // std::cout << "iniciando rondando senyuelo" << '\n';
    }
    yo->destino=yo->playerPos;


    rond();

}
void Action::rond(){
    if(s!=BH_RUNNING){
        yo->rondacion_cont=0;
        s=BH_RUNNING;

    }

    float cont= yo->rondacion_cont;
    cont++;
    if(cont>50){
        s=BH_SUCCESS;
    }

    CTransform* cTransform;     //  Punteros a otras componentes
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,yo->getEntityID()));
    gg::Vector3f mio =cTransform->getPosition();

    gg::Vector3f dest =yo->destino;

    //// std::cout << "dest" <<dest<< '\n';
    //gg::Normalice(dest-mio)*2;
    gg::Vector3f res=dest-mio;
    gg::Vector3f res2=mio+gg::Normalice(gg::Vector3f(res.Z,0,-res.X))*1/15;
    //// std::cout << "mio" <<mio<< '\n';
    //// std::cout << "posicion" <<res2<< '\n';

    cTransform->setPosition(mio+gg::Normalice(gg::Vector3f(res.Z,0,-res.X))*1/15);
    //float dist=gg::DIST(mio,dest);
    //// std::cout << "dist" <<dist<< '\n';
    //if(dist<5){
    //    s=BH_SUCCESS;
    //}else{
    //    s=BH_RUNNING;
    //}

}
void Action::ult_cont(){
    float res=yo->ultrasonido_cont;
    res++;
    //3-4 seg
    if(res>100){
        //// std::cout << "aturdido acabado" << '\n';
        yo->ultrasonido=false;



        s=BH_SUCCESS;
    }else{
        s=BH_RUNNING;
    }
    yo->ultrasonido_cont=res;
    //data->setData("ultrasonido_cont",new BInt(0));

}

void Action::distancia(float _dist,gg::Vector3f obj){//int tipo){


    CTransform* cTransform;     //  Punteros a otras componentes
    float id=yo->getEntityID();

    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,id));
    gg::Vector3f mio =cTransform->getPosition();

    float dist=gg::DIST(mio,obj);
    if(dist<_dist){
        s=BH_SUCCESS;

    }else{
        s=BH_FAILURE;

    }

}
void Action::comer_animal(){
    setActive("comer",1);
}
void Action::girar_enemigo(){
    setActive("girar",0);
}
void Action::rango_visual(){
    setActive("rango",1);
}
void Action::move_to(){
    setActive("mover",1);
}
void Action::move_last(){

    if(s!=BH_RUNNING){
        s=BH_RUNNING;

        //// std::cout << "iniciando move last" << '\n';
        yo->destino=yo->playerPos;
    }
    move_too();
    if(s!=BH_RUNNING){
        yo->playerSeen=false;
    }
}
void Action::move_senyuelo(){
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        //// std::cout << "iniciando move senyuelo" << '\n';

    }

    yo->destino=yo->senpos;

    move_too();
}
void Action::player_vistocono(){
    CTransform* cTransform;     //  Punteros a otras componentes
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,data->getBData("id2")->getInt()));
    gg::Vector3f player=cTransform->getPosition();

    //CTransform* cTransform;     //  Punteros a otras componentes
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,yo->getEntityID()));
    float rotate=cTransform->getRotation().Y;//grados


}
void Action::move_player(){
    //std::co << "move player" << '\n';
    //// std::cout << "moviendo" << '\n';
    //if(s!=BH_RUNNING){

    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        //// std::cout << "iniciando move PLAYER" << '\n';

    }
    //}
    CTransform* cTransform;     //  Punteros a otras componentes
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,data->getBData("id2")->getInt()));
    yo->destino=cTransform->getPosition();

    move_too();
}

void Action::move_around(){
    if(s!=BH_RUNNING){
        //// std::cout << "iniciando move random" << '\n';

    }
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        //elegir
        //// std::cout << "elegimos" << '\n';
        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<int> distribution(-50,50);
        int x = distribution(gen);
        int y = distribution(gen);
        //// std::cout << "X:" <<x<< '\n';
        //// std::cout << "Y" <<y<< '\n';
        CTransform* cTransform;     //  Punteros a otras componentes
        cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,yo->getEntityID()));
        gg::Vector3f mio =cTransform->getPosition();
        //// std::cout << "mio:" <<mio << '\n';
        gg::Vector3f dest =mio+gg::Vector3f(x,0,y);
        //// std::cout << "dest:" <<dest << '\n';
        //cTransform->setPosition(mio);
        yo->destino=dest;


    }
    move_too();
}

void Action::move_too(){
    CTransform* cTransform;     //  Punteros a otras componentes
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM,yo->getEntityID()));
    gg::Vector3f mio =cTransform->getPosition();
    //// std::cout << "mio" <<mio<< '\n';

    gg::Vector3f dest =yo->destino;
    //// std::cout << "dest" <<dest<< '\n';
    //gg::Normalice(dest-mio)*2;
    cTransform->setPosition(mio+gg::Normalice(dest-mio)*1/15);
    float dist=gg::DIST(mio,dest);
    //// std::cout << "dist" <<dist<< '\n';
    if(dist<10){
        s=BH_SUCCESS;
    }else{
        s=BH_RUNNING;
    }

}
void Action::onTerminate(Status state){//tener cuidado de cerrar todos los recursos que abramos
  //// std::cout << "Accion onTerminate" <<state << '\n';
}
