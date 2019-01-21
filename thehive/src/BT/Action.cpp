#include "Action.hpp"

#include "EventSystem/Blackboard.hpp"
#include "EventSystem/BVector3f.hpp"
#include "EventSystem/BInt.hpp"
#include "EventSystem/BBool.hpp"

#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/Components/CAIEnem.hpp>
#include <ComponentArch/Components/CTransform.hpp>
#include <ComponentArch/Components/CRigidBody.hpp>
#include <ComponentArch/Components/CVida.hpp>

#include <GameAI/Pathfinding.hpp>

#define MAX_AI_SPEED            2.f
#define VEL_ATENUATION          0.1

int Action::aliensAttacking = 0;

Action::Action(const Action &orig){
    Action(orig.tarea,orig.data,orig.yo);
}
int Action::getTask(){
    return tarea;
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

    VectorAcciones[ALLY_DEAD]               = &Action::isThereSomeAlienDead;    // COMENTADO -> NO SE UTILIZA
    VectorAcciones[MORE_RAGE]               = &Action::moreRage;                // COMENTADO -> NO SE UTILIZA
    VectorAcciones[X_ALIENS_ATTACKING]      = &Action::checkAliensAttacking;   // si

    VectorAcciones[X_METRES_PLAYER]         = &Action::distancia20;     // si
    VectorAcciones[RONDAR_PLAYER]           = &Action::rond_jugador;    // si
    VectorAcciones[PAUSE]                   = &Action::alienInPause;    // si

    VectorAcciones[MOVE_TO_PLAYER]          = &Action::move_player;     // si
    VectorAcciones[PLAYER_SEEN]             = &Action::seen;            // si
    VectorAcciones[MOVE_AROUND]             = &Action::move_around;     // si -> ES EL RANDOM WALK
    VectorAcciones[MOVE_TO_LAST_POS_KWON]   = &Action::move_last;       // si
    VectorAcciones[IN_LAST_POS_KWON]        = &Action::in_last;         // si

    VectorAcciones[FIVE_SINCELASTHABILITY]  = &Action::FIVE_SinceLastHability;
    VectorAcciones[EXPANSIVE_WAVE]          = &Action::doExplosiveWave;
    VectorAcciones[SPIT]                    = &Action::doSpit;
    VectorAcciones[ENEMY_OVER_2_METERS]     = &Action::over_2_meters;

    VectorAcciones[MOVEP_UNTILX]            = &Action::move_player_utilx;         // si
    VectorAcciones[IAMATACKING]            = &Action::imatack;         // si

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
    s = BH_INVALID;
}//parámetros del mundo necesarios para el update} // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Action::update() {

    if(VectorAcciones[tarea] != nullptr)
        (this->*VectorAcciones[tarea])();

    return s;

}// Update del comportamiento. Llamado cada vez que el comportamiento es actualizado

void Action::abort(){
    Behavior::abort();
    //modifyImAttacking(false);
}

void Action::setActive(std::string a, bool acierto){
    if(acierto)
        s = BH_SUCCESS;
    else
        s = BH_FAILURE;
}

void Action::andar_random(){
    setActive("andar random",0);

}

void Action::in_last(){//int tipo){
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
    }else{
        s=BH_FAILURE;
    }
}

void Action::onrange(){
    checkbool(yo->playerOnRange);

}

void Action::seeing(){
    checkbool(yo->playerSeeing);

}

void Action::ultrasonido(){
    checkbool(yo->ultrasonido);
}

void Action::senyuelo(){
    checkbool(yo->senyuelo);

}
void Action::imatack(){
    checkbool(yo->getImAttacking());

}

void Action::seen(){
    checkbool(yo->playerSeen);

}

void Action::rond_seny(){
    if(s!=BH_RUNNING){
        // gg::cout("RONDANDO SENYUELO");
        yo->destino=yo->senpos;
        yo->rondacion_cont=0;
        s=BH_RUNNING;
        int sign;
        gg::genFloatRandom(-1,1)>0? sign = 1 : sign = -1;
        yo->setSigno(sign);
    }
    rond();

}

void Action::rond_jugador(){
    if(s!=BH_RUNNING){
        //gg::cout("RONDANDO JUGADOR");
        yo->rondacion_cont=0;
        s=BH_RUNNING;
        int sign;
        gg::genFloatRandom(-1,1)>0? sign = 1 : sign = -1;
        yo->setSigno(sign);
    }
    yo->destino=yo->playerPos;
    rond(yo->playerSeeing);
}

void Action::rond(bool _b){
    // El bool que se le pasa es dependiendo si se le llama desde:
    //      rond_jugador    -> Necesita el bool de si ve al jugador
    //      rond_seny       -> No necesita ningun bool para pasar
    // ADEMAS: El bool es true por defecto
    float cont= yo->rondacion_cont;
    cont++;

    if(cont>50){
        s=BH_SUCCESS;
        return;
    }
//2-3 seg
    // Intentar cambiar esto
    int sign = yo->getSigno();
    //gg::genFloatRandom(-1,1)>0? sign = 1 : sign = -1;

    gg::Vector3f mio            = cTransform->getPosition();
    gg::Vector3f dest           = yo->destino;

    gg::Vector3f V_AI_DEST      = dest-mio;
    gg::Vector3f V_AI_DEST_PP   = gg::Vector3f(sign*V_AI_DEST.Z,0,(-sign)*V_AI_DEST.X);
    gg::Vector3f V_FINAL        = gg::Normalice(V_AI_DEST_PP);

    V_AI_DEST.Y     = 0;
    V_AI_DEST       = gg::Normalice(V_AI_DEST);
    V_FINAL         =(V_FINAL+V_AI_DEST*0.1);
    V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

    cTransform->setRotation(V_AI_DEST);

    cRigidBody->applyConstantVelocity(V_FINAL,MAX_AI_SPEED-(yo->getEnemyType()*VEL_ATENUATION));
}

void Action::ult_cont(){
    float res=yo->ultrasonido_cont;
    res++;
    //3-4 seg
    if(res>100){
        yo->ultrasonido=false;

        s=BH_SUCCESS;
    }else{
        s=BH_RUNNING;
    }
    yo->ultrasonido_cont=res;
    //data->setData("ultrasonido_cont",new BInt(0));

}

void Action::distancia10(){//int tipo){
    distancia(10,yo->playerPos);//int tipo){
}

void Action::distancia20(){
    distancia(20,yo->playerPos);//int tipo){
}

void Action::distancia(float _dist,gg::Vector3f obj){//int tipo){
    gg::Vector3f mio    = cTransform->getPosition();
    mio.Y=0;
    obj.Y=0;
    float dist          = gg::DIST(mio,obj);

    if(dist<_dist){
        s = BH_SUCCESS;
    }else{
        s = BH_FAILURE;
    }

}

void Action::over_2_meters(){
    over_X_meters(2);
}

void Action::over_X_meters(int _m){
    gg::Vector3f obj    = yo->playerPos;
    gg::Vector3f mio    = cTransform->getPosition();

    mio.Y=0;
    obj.Y=0;

    float dist          = gg::DIST(mio,obj);

    (dist>_m)? s = BH_SUCCESS : s = BH_FAILURE;
}

void Action::hit(){
    gg::Vector3f mio            = cTransform->getPosition();
    gg::Vector3f dest           = yo->playerPos;

    gg::Vector3f V_AI_DEST      = dest-mio;

    V_AI_DEST.Y     = 0;
    V_AI_DEST       = gg::Normalice(V_AI_DEST);
    V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

    cTransform->setRotation(V_AI_DEST);

    if(s!=BH_RUNNING){
        cont_hit = 0;
        modifyImAttacking(true);

        uint16_t hero = manager->getHeroID();
        CVida *ht = static_cast<CVida*>(manager->getComponent(gg::VIDA, hero));
        ht->quitarvida(0.5+(yo->getRage()/2));

        s = BH_RUNNING;
    }

    cont_hit++;
    if(cont_hit > 50){
        //modifyImAttacking(false);
        s = BH_SUCCESS;
    }
}

void Action::playerNotAttacking(){
    if(yo->getPlayerIsAttacking()){
        s = BH_FAILURE;
        modifyImAttacking(true);
    }
    else{
        // gg::cout("NO ATTACK");
        s = BH_SUCCESS;
    }
}

void Action::isThereSomeAlienDead(){
    // NO SE USA
    // _________
    // gg::cout("SOME ALIEN DEAD?");
    // if(yo->getCloserAllyIsDead()){
    //     gg::cout(" -- SI CARACULO");
    //     s = BH_SUCCESS;
    // }
    // else{
    //     gg::cout(" -- PUES NO");
    //     s = BH_FAILURE;
    // }
}

void Action::moreRage(){
    // NO SE USA
    // _________
    // gg::cout("-- -----------------------");
    // yo->upgradeRage();
    // s = BH_SUCCESS;
}

void Action::checkAliensAttacking(){
    if(aliensAttacking <= yo->getMaxAliensAttackingAtOnce() && !yo->getImAttacking()){
        modifyImAttacking(true);
        s = BH_FAILURE;
    }
    else{
        s = BH_SUCCESS;
    }

}

void Action::alienInPause(){
    if(s!=BH_RUNNING){
        cont_pause = 0;
        s = BH_RUNNING;
    }
    cont_pause++;
    if(cont_pause > 50){
        s = BH_SUCCESS;
    }

}

void Action::comer_animal(){
    s = BH_SUCCESS;

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
        //gg::cout("move last");
        s=BH_RUNNING;
        yo->destino = yo->playerPos;
    }

    move_too(10);

    if(s==BH_SUCCESS){
        yo->playerSeen=false;
    }
}

void Action::move_senyuelo(){
    if(s!=BH_RUNNING){
        //gg::cout("move senyuelo");
        s=BH_RUNNING;
        yo->destino = yo->senpos;
    }

    move_too(10);
}

///
void Action::move_player_utilx(){
    //10-25
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        //gg::cout("move player");

        // gg::cout(" --- MOVE TO PLAYER --- ");
    }
    CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,manager->getHeroID()));
    yo->destino = cTransform2->getPosition();

    move_too(15);
}
void Action::move_player(){
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        //gg::cout("move player");

        // gg::cout(" --- MOVE TO PLAYER --- ");
    }

    CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,manager->getHeroID()));
    yo->destino = cTransform2->getPosition();

    move_too(5);
    if(s==BH_SUCCESS){
        yo->playerSeen=false;
    }
}

void Action::move_around(){
    CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
    if(nvAgent){
        if(s!=BH_RUNNING){
            s=BH_RUNNING;
            // Obligatorio
            nvAgent->ResetDestination();

            gg::Vector3f dest = Singleton<Pathfinding>::Instance()->getRandomNodePosition();

            yo->destino = cTransform->getPosition();

            nvAgent->SetDestination(dest);
        }
        if(s==BH_RUNNING){
            // Intercambio EL USO DE LOS VECTORES dest y mio
            gg::Vector3f dest           = cTransform->getPosition();    // A donde voy
            gg::Vector3f mio            = yo->destino;                  // Donde estaba

            gg::Vector3f V_AI_DEST      = dest-mio;

            V_AI_DEST.Y     = 0;
            V_AI_DEST       = gg::Normalice(V_AI_DEST);
            V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

            cTransform->setRotation(V_AI_DEST);

            yo->destino = cTransform->getPosition();

            if(!nvAgent->HasDestination()){
                nvAgent->ResetDestination();
                s = BH_SUCCESS;
            }
        }
    }
    else{
        s = BH_SUCCESS;
    }
}

void Action::move_too(int min){
    gg::Vector3f mio        = cTransform->getPosition();
    gg::Vector3f dest       = yo->destino;
    gg::Vector3f direccion  = dest-mio;

    // direccion.Y     = 0;
    // direccion       = gg::Normalice(direccion);
    // direccion       = gg::Direccion2D_to_rot(direccion);
    //
    // cTransform->setRotation(direccion);
    //
    // direccion       = dest-mio;
    // direccion       = gg::Normalice(direccion);
    // cRigidBody->applyConstantVelocity(direccion,MAX_AI_SPEED-(yo->getEnemyType()*VEL_ATENUATION));

    mio.Y=0;
    dest.Y=0;
    float dist = gg::DIST(mio,dest);

    if(dist<min){
        s = BH_SUCCESS;
    }
    else{
        s = BH_RUNNING;
    mio=direccion;
    mio.Y     = 0;
    mio       = gg::Normalice(mio);
    mio       = gg::Direccion2D_to_rot(mio);

    cTransform->setRotation(mio);

    direccion       = gg::Normalice(direccion);
    cRigidBody->applyConstantVelocity(direccion,MAX_AI_SPEED);
}


}

void Action::onTerminate(Status state){//tener cuidado de cerrar todos los recursos que abramos
  // gg::cout("ON TERMINATE: ["+std::to_string(state)+"]");
}

void Action::modifyImAttacking(bool _b){
    if(!_b){
        if(yo->getImAttacking()){
            if(aliensAttacking>0) aliensAttacking--;
            yo->setImAttacking(false);
        }
    }
    else{
        if(!yo->getImAttacking()){
            aliensAttacking++;
            yo->setImAttacking(true);
        }
    }
}

void Action::setOffsetAliensAttacking(int _i){
    aliensAttacking += _i;
}

void Action::FIVE_SinceLastHability(){
    gg::cout(yo->getHabilityUpdateCounter());
    if(yo->getHabilityUpdateCounter() > 300){
        yo->resetHabilityUpdateCounter();
        s = BH_SUCCESS;
    }
    else{
        s = BH_FAILURE;
    }
}

void Action::doExplosiveWave(){
    yo->explosiveWave();
    s = BH_FAILURE;
}

void Action::doSpit(){
    gg::cout("SPIT!");
    // yo->spit();
    s = BH_SUCCESS;
}
