#include "Action.hpp"

#define MAX_AI_SPEED            1.5
#define MAX_ALIENS_ATTACKING    1

int Action::aliensAttacking = 0;

Action::Action(const Action &orig){
    Action(orig.tarea,orig.data,orig.yo);
}

Action::Action(Hojas task,Blackboard* _data,CAIEnem* ai){
    yo = ai;

    VectorAcciones[ANDAR_RAND]              = &Action::andar_random;
    VectorAcciones[COMER]                   = &Action::comer_animal;
    VectorAcciones[GIRAR]                   = &Action::girar_enemigo;
    VectorAcciones[RANGO]                   = &Action::rango_visual;
    VectorAcciones[MOVER]                   = &Action::move_to;

    VectorAcciones[TEN_METROS]              = &Action::distancia10;     // si
    VectorAcciones[THREE_ATACK]             = &Action::move_to;         // ni idea si
    VectorAcciones[IN_PLACE]                = &Action::move_to;         // inutilidad maxima si
    VectorAcciones[BLOCK]                   = &Action::move_around;     // trucada
    VectorAcciones[JUST_MOVE]               = &Action::move_around;     // trucada

    VectorAcciones[RANGO_ULTRASONIDO]       = &Action::ultrasonido;     // si
    VectorAcciones[ATURDIDO]                = &Action::ult_cont;        // si
    VectorAcciones[RANGO_SENYUELO]          = &Action::senyuelo;        // si
    VectorAcciones[MOVER_SENYUELO]          = &Action::move_senyuelo;   // si
    VectorAcciones[RONDAR_SENYUELO]         = &Action::rond_seny;       // si
    VectorAcciones[PLAYER_SEEING]           = &Action::seeing;          // si
    VectorAcciones[ON_RANGE]                = &Action::onrange;         // si
    VectorAcciones[HIT]                     = &Action::hit;             // si
    VectorAcciones[NOT_ATTACKED]            = &Action::playerNotAttacking;   // si

    VectorAcciones[ALLY_DEAD]               = &Action::isThereSomeAlienDead;   // si
    VectorAcciones[MORE_RAGE]               = &Action::moreRage;    // si
    VectorAcciones[X_ALIENS_ATTACKING]      = &Action::checkAliensAttacking;   // si

    VectorAcciones[X_METRES_PLAYER]         = &Action::distancia10;     // SI
    VectorAcciones[RONDAR_PLAYER]           = &Action::rond_jugador;    // si
    VectorAcciones[PAUSE]                   = &Action::comer_animal;    // TRUCADA
    VectorAcciones[MOVE_TO_PLAYER]          = &Action::move_player;     // si
    VectorAcciones[PLAYER_SEEN]             = &Action::seen;            // si
    VectorAcciones[MOVE_AROUND]             = &Action::move_around;     // siRANDOM
    VectorAcciones[MOVE_TO_LAST_POS_KWON]   = &Action::move_last;       // si
    VectorAcciones[IN_LAST_POS_KWON]        = &Action::in_last;         // si

    data    = _data;
    tarea   = task;

    manager = Singleton<ObjectManager>::Instance();

    cTransform = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,yo->getEntityID()));
    cRigidBody = static_cast<CRigidBody*>(manager->getComponent(gg::RIGID_BODY,yo->getEntityID()));
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

    if(VectorAcciones[tarea] != nullptr)
        (this->*VectorAcciones[tarea])();

    return s;

}// Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Action::setActive(std::string a, bool acierto){
    if(acierto)
        s = BH_SUCCESS;
    else
        s = BH_FAILURE;
}

void Action::andar_random(){
    setActive("andar random",0);

}

void Action::distancia10(){//int tipo){
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
        // gg::cout("RONDANDO SENYUELO");
        yo->destino=yo->senpos;
    }
    rond();

}

void Action::rond_jugador(){
    if(s!=BH_RUNNING){
        // gg::cout("RONDANDO JUGADOR");
        yo->destino=yo->playerPos;
    }


    rond(yo->playerSeeing);

}

void Action::rond(bool _b){
    // El bool que se le pasa es dependiendo si se le llama desde:
    //      rond_jugador    -> Necesita el bool de si ve al jugador
    //      rond_seny       -> No necesita ningun bool para pasar
    // ADEMAS: El bool es true por defecto
    if(s!=BH_RUNNING){
        yo->rondacion_cont=0;
        s=BH_RUNNING;
    }

    float cont= yo->rondacion_cont;
    cont++;

    if(cont>50 || !_b){
        s=BH_SUCCESS;
    }

    gg::Vector3f mio            = cTransform->getPosition();
    gg::Vector3f dest           = yo->destino;

    gg::Vector3f V_AI_DEST      = dest-mio;
    gg::Vector3f V_AI_DEST_PP   = gg::Vector3f(V_AI_DEST.Z,0,-V_AI_DEST.X);
    gg::Vector3f V_FINAL        = (V_AI_DEST-V_AI_DEST_PP)*0.3;

    cRigidBody->applyConstantVelocity(V_FINAL,MAX_AI_SPEED);
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
    gg::Vector3f mio    = cTransform->getPosition();
    float dist          = gg::DIST(mio,obj);

    if(dist<_dist){
        s = BH_SUCCESS;
    }else{
        s = BH_FAILURE;
    }

}

void Action::hit(){
    if(s!=BH_RUNNING){
        aliensAttacking++;
        cont_hit = 0;
        s = BH_RUNNING;
    }

    cont_hit++;
    if(cont_hit > 50){
        // Cuando ataque checkear que tambien este a rango
        uint16_t hero = manager->getHeroID();
        CVida *ht = static_cast<CVida*>(manager->getComponent(gg::VIDA, hero));

        ht->quitarvida(0.5+(yo->getRage()/2));
        aliensAttacking--;
        s = BH_SUCCESS;
    }
}

void Action::playerNotAttacking(){
    if(s != BH_RUNNING){
        s = BH_RUNNING;
    }

    if(yo->getPlayerIsAttacking()){
        s = BH_FAILURE;
    }
    else{
        s = BH_SUCCESS;
    }
}

void Action::isThereSomeAlienDead(){
    if(yo->getCloserAllyIsDead()){
        s = BH_SUCCESS;
    }
    else{
        s = BH_FAILURE;
    }
}

void Action::moreRage(){
    yo->upgradeRage();
    s = BH_SUCCESS;
}

void Action::checkAliensAttacking(){
    if(aliensAttacking<MAX_ALIENS_ATTACKING){
        s = BH_SUCCESS;
    }
    else{
        s = BH_FAILURE;
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
        yo->destino = yo->playerPos;
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
        yo->destino = yo->senpos;
    }

    move_too();
}

void Action::player_vistocono(){
    // PABLO: Esta comentado, pero no se si se usa para algo
    // CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,data->getBData("id2")->getInt()));
    // gg::Vector3f player=cTransform2->getPosition();

    float rotate=cTransform->getRotation().Y;//grados
}

void Action::move_player(){
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        //// std::cout << "iniciando move PLAYER" << '\n';
    }
    CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,data->getBData("id2")->getInt()));
    yo->destino = cTransform2->getPosition();

    move_too();
}

void Action::move_around(){
    if(s!=BH_RUNNING){
        s=BH_RUNNING;

        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_int_distribution<int> distribution(-50,50);
        int x = distribution(gen);
        int y = distribution(gen);

        gg::Vector3f mio    = cTransform->getPosition();
        gg::Vector3f dest   = mio+gg::Vector3f(x,0,y);
        yo->destino         = dest;
    }
    move_too();
}

void Action::move_too(){
    gg::Vector3f mio        = cTransform->getPosition();
    gg::Vector3f dest       = yo->destino;
    gg::Vector3f direccion  = dest-mio;

    direccion.Y     = 0;
    direccion       = gg::Normalice(direccion);
    direccion       = gg::Direccion2D_to_rot(direccion);

    cTransform->setRotation(direccion);

    direccion       = dest-mio;
    direccion       = gg::Normalice(direccion);
    cRigidBody->applyConstantVelocity(direccion,MAX_AI_SPEED);

    float dist = gg::DIST(mio,dest);

    if(dist<10)     s = BH_SUCCESS;
    else            s = BH_RUNNING;

}

void Action::onTerminate(Status state){//tener cuidado de cerrar todos los recursos que abramos
  // gg::cout("ON TERMINATE: ["+std::to_string(state)+"]");
}
