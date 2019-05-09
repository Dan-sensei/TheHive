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
#include <ComponentArch/Components/CNavmeshAgent.hpp>
#include <ComponentArch/Components/CFlock.hpp>

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
    s=BH_INVALID;
    //m_eStatus=BH_INVALID;
    SetStatus(BH_INVALID);

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
    VectorAcciones[IAMATACKING]             = &Action::imatack;         // si

    VectorAcciones[PRE_DASH_TO_PLAYER]      = &Action::predash_to_player;         // nope
    VectorAcciones[PRE_DASH_TO_LAST_PLAYER] = &Action::predash_to_last_player;         // nope
    VectorAcciones[DASH]                    = &Action::dash;         // nope

    VectorAcciones[IAMLEADER]               = &Action::leader;         // nope
    VectorAcciones[FOLLOWLEADER]            = &Action::move_leader;         // nope
    VectorAcciones[KAMIKACE]                = &Action::kamikace;         // nope

    VectorAcciones[LOOKAROUND]                = &Action::look_around;         // nope

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
    SetStatus(BH_INVALID);
}//parámetros del mundo necesarios para el update} // Es llamado UNA VEZ e inmediatamente antes de la primera llamada del update

Status Action::update() {

    if(VectorAcciones[tarea] != nullptr)
        (this->*VectorAcciones[tarea])();
        SetStatus(s);


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

void Action::leader(){
    CFlock* cFlock = static_cast<CFlock*>(manager->getComponent(gg::FLOCK,yo->getEntityID()));
    if(cFlock){
        checkbool(cFlock->getLeader());
    }
    else{
        s=BH_SUCCESS;
    }
////std::cout << s << '\n';
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
        // //gg::cout("RONDANDO SENYUELO");
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
        ////gg::cout("RONDANDO JUGADOR");
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

    glm::vec3 mio            = cTransform->getPosition();
    glm::vec3 dest           = yo->destino;

    glm::vec3 V_AI_DEST      = dest-mio;
    glm::vec3 V_AI_DEST_PP   = glm::vec3(sign*V_AI_DEST.z,0,(-sign)*V_AI_DEST.x);
    glm::vec3 V_FINAL        = glm::normalize(V_AI_DEST_PP);

    V_AI_DEST.y     = 0;
    V_AI_DEST       = glm::normalize(V_AI_DEST);
    V_FINAL         =(V_FINAL+V_AI_DEST*0.1f);
    V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

    cTransform->setRotation(V_AI_DEST);

    cRigidBody->applyConstantVelocityNormal(V_FINAL,yo->getVelocity()-(yo->getEnemyType()*VEL_ATENUATION));
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

void Action::distancia(float _dist,glm::vec3 obj){//int tipo){
    glm::vec3 mio    = cTransform->getPosition();
    mio.y=0;
    obj.y=0;
    float dist          = glm::distance(mio,obj);

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
    glm::vec3 obj    = yo->playerPos;
    glm::vec3 mio    = cTransform->getPosition();

    mio.y=0;
    obj.y=0;

    float dist          = glm::distance(mio,obj);

    (dist>_m)? s = BH_SUCCESS : s = BH_FAILURE;
}

void Action::dash(){
    if(s!=BH_RUNNING){
        CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
        if(nvAgent){
            nvAgent->ResetDestination();
        }
    }
    move_too(5);

}
void Action::predash_to_last_player(){

    if(s!=BH_RUNNING){

        if(glm::distance(yo->destino,yo->playerPos)>30){
            glm::vec3 mio            = cTransform->getPosition();
            yo->destino = mio +glm::normalize(yo->playerPos-mio)*30.f;
        }
        else{
            yo->destino = yo->playerPos;
        }
        //yo->destino = yo->playerPos;
    }
    predash();
    if(s!=BH_RUNNING&&yo->destino == yo->playerPos){
        yo->playerSeen=false;
    }
}
void Action::predash_to_player(){
    if(s!=BH_RUNNING){
        glm::vec3 mio            = cTransform->getPosition();
        CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,manager->getHeroID()));
        //yo->destino = mio +glm::normalize(cTransform2->getPosition()-mio)*30;
        yo->destino = cTransform2->getPosition();
    }
    predash();
    if(s!=BH_RUNNING){
        glm::vec3 mio            = cTransform->getPosition();
        CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,manager->getHeroID()));
        if(glm::distance(cTransform2->getPosition(),mio)<5){
            uint16_t hero = manager->getHeroID();
            CVida *ht = static_cast<CVida*>(manager->getComponent(gg::VIDA, hero));
            ht->quitarvida(0.5+(yo->getRage()/2));

        }
    }
}
void Action::predash(){

    if(s!=BH_RUNNING){
        CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
        if(nvAgent){
            nvAgent->ResetDestination();
        }
        s = BH_RUNNING;
        //elegir destino y ponemos rotacion
        glm::vec3 mio            = cTransform->getPosition();
        glm::vec3 dest           = yo->destino;
        glm::vec3 V_AI_DEST      = dest-mio;
        //yo->destino = yo->playerPos;

        V_AI_DEST.y     = 0;
        V_AI_DEST       = glm::normalize(V_AI_DEST);
        V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

        cTransform->setRotation(V_AI_DEST);
        //inicializamos variables
        cont_hit = 0;
    }
    cont_hit++;
    if(cont_hit > 50){
        s = BH_SUCCESS;
    }

}
void Action::kamikace(){
    uint16_t hero = manager->getHeroID();
    CVida *ht = static_cast<CVida*>(manager->getComponent(gg::VIDA, hero));
    ht->quitarvida(0.5+(yo->getRage()/2));

    CVida *mio = static_cast<CVida*>(manager->getComponent(gg::VIDA, yo->getEntityID()));
    mio->Muerte();
    s=BH_SUCCESS;


}
void Action::look_around(){
    if(s!=BH_RUNNING){
        s = BH_RUNNING;
        yo->ultrasonido_cont    = 0;
        int num =gg::genIntRandom(1,2);
        yo->signo=pow(-1,num);
    }
    yo->ultrasonido_cont++;
    // cTransform->setRotation(cTransform->getRotation()+glm::vec3(0,yo->signo,0));
    cTransform->rotate(glm::radians(static_cast<float>(yo->signo)), glm::vec3(0,1,0));
    if(yo->ultrasonido_cont==30){
        yo->signo=yo->signo*-1;
    }
    if(yo->ultrasonido_cont==60){
        s = BH_SUCCESS;
    }

}
void Action::hit(){
    ////std::cout << yo->playerOnRange << '\n';
    //if(yo->playerOnRange){
    //    //std::cout << "estoy a rango" << '\n';
    //}else{
    //    //std::cout << "no lo estoy" << '\n';
    //}
    glm::vec3 mio            = cTransform->getPosition();
    glm::vec3 dest           = yo->playerPos;

    glm::vec3 V_AI_DEST      = dest-mio;

    V_AI_DEST.y     = 0;
    V_AI_DEST       = glm::normalize(V_AI_DEST);
    V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

    cTransform->setRotation(V_AI_DEST);

    if(s!=BH_RUNNING){
        cRigidBody->setLinearVelocity(glm::vec3());
        CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
        if(nvAgent){
            nvAgent->ResetDestination();
        }
        cont_hit = 0;
        modifyImAttacking(true);

        uint16_t hero = manager->getHeroID();
        CVida *ht = static_cast<CVida*>(manager->getComponent(gg::VIDA, hero));
        ht->quitarvida(0.5+(yo->getRage()/2));

        s = BH_RUNNING;

        yo->playAttack();
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
        // //gg::cout("NO ATTACK");
        s = BH_SUCCESS;
    }
}

void Action::isThereSomeAlienDead(){
    // NO SE USA
    // _________
    // //gg::cout("SOME ALIEN DEAD?");
    // if(yo->getCloserAllyIsDead()){
    //     //gg::cout(" -- SI CARACULO");
    //     s = BH_SUCCESS;
    // }
    // else{
    //     //gg::cout(" -- PUES NO");
    //     s = BH_FAILURE;
    // }
}

void Action::moreRage(){
    // NO SE USA
    // _________
    // //gg::cout("-- -----------------------");
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


void Action::move_senyuelo(){
    if(s!=BH_RUNNING){
        ////std::cout << "last final" << '\n';
        //gg::cout("move senyuelo");
        s=BH_RUNNING;
        CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
        if(nvAgent){
            nvAgent->ResetDestination();
        }
        yo->destino = yo->senpos;
    }

    move_too(10);
}

///
void Action::move_leader(){
    //10-25
    ////std::cout << "se hace" << '\n';
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        //gg::cout("move player");

        // gg::cout(" --- MOVE TO PLAYER --- ");
    }
    CFlock* cF = static_cast<CFlock*>(manager->getComponent(gg::FLOCK,yo->getEntityID()));
    if(cF){
        CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,cF->getLeaderID()));
        CRigidBody* body = static_cast<CRigidBody*>(manager->getComponent(gg::RIGID_BODY,cF->getLeaderID()));
        glm::vec3 mio        = cTransform->getPosition();
        glm::vec3 suyo        = cTransform2->getPosition();
        float dist = glm::distance(mio,suyo);
        if(dist<4){
            s=BH_SUCCESS;
        }
        else if(dist>10){
            //s = BH_RUNNING;
            glm::vec3 direccion  = suyo-mio;
            if(direccion.x==0 &&direccion.z==0){
                std::cout << "nulo" << '\n';
            }else{
                direccion       = glm::normalize(direccion);
                cRigidBody->applyConstantVelocityNormal(direccion,yo->getVelocity());

                direccion.y     = 0;
                direccion       = glm::normalize(direccion);
                direccion       = gg::Direccion2D_to_rot(direccion);
                cTransform->setRotation(direccion);
            }



        }else{
            glm::vec3 vel=body->getVelocity();
            if(vel.x==0 && vel.z==0){
                std::cout << "nulo" << '\n';
            }else{
                vel.y=0;
                cRigidBody->applyConstantVelocityNormal(glm::normalize(vel),yo->getVelocity());

            }
        }
    }
    else{
        s=BH_FAILURE;

    }

}
void Action::move_player_utilx(){
    //10-25
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        ////gg::cout("move player");

        // //gg::cout(" --- MOVE TO PLAYER --- ");
    }
    CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,manager->getHeroID()));
    yo->destino = cTransform2->getPosition();

    move_too(15);
}
void Action::move_player(){
    if(s!=BH_RUNNING){
        s=BH_RUNNING;
        CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
        if(nvAgent){
            nvAgent->ResetDestination();
        }
        ////std::cout << "move player inicio" << '\n';
        //gg::cout("move player");

        // //gg::cout(" --- MOVE TO PLAYER --- ");
        // //std::cout << "empieza" << '\n';
    }

    CTransform* cTransform2 = static_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,manager->getHeroID()));
    yo->destino = cTransform2->getPosition();

    ////std::cout << "move player" << '\n';

    move_too(yo->getArange());//rango de ataque
    if(s!=BH_RUNNING){
        ////std::cout << "move player final" << '\n';
        //gg::cout("move player");

        // //gg::cout(" --- MOVE TO PLAYER --- ");
        // //std::cout << "acaba" << '\n';
    }
    //if(s==BH_SUCCESS){
    //    yo->playerSeen=false;
    //}
}


void Action::move_last(){
    CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
    if(nvAgent){
        if(s!=BH_RUNNING){
            nvAgent->ResetDestination();
            std::cout << "empieza" << '\n';
            s=BH_RUNNING;
            // Obligatorio
            //glm::vec3 dest = Singleton<Pathfinding>::Instance()->getRandomNodePosition();
            yo->destino = cTransform->getPosition();
            nvAgent->SetDestination(yo->playerPos);
            if(!nvAgent->HasDestination()){
                std::cout << "falla esto" << '\n';
            }
            return;
        }
        if(s==BH_RUNNING){
            // Intercambio EL USO DE LOS VECTORES dest y mio
            glm::vec3 dest           = cTransform->getPosition();    // A donde voy
            glm::vec3 mio            = yo->destino;                  // Donde estaba

            ////std::cout << "dest" <<dest<< '\n';
            ////std::cout << "mio" <<mio<< '\n';

            glm::vec3 V_AI_DEST      = dest-mio;
            if(!(dest==mio)){


                V_AI_DEST.y     = 0;
                V_AI_DEST       = glm::normalize(V_AI_DEST);
                V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

                cTransform->setRotation(V_AI_DEST);

                yo->destino = cTransform->getPosition();
            }

            if(!nvAgent->HasDestination()){
                std::cout << "acaba1" << '\n';

                nvAgent->ResetDestination();
                s = BH_SUCCESS;
                yo->playerSeen=false;
            }
        }
    }
    else{
        std::cout << "acaba2" << '\n';

        yo->playerSeen=false;
        s = BH_SUCCESS;
    }
}
void Action::move_around(){
    CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(manager->getComponent(gg::NAVMESHAGENT,yo->getEntityID()));
    if(nvAgent){
        if(s!=BH_RUNNING){
            nvAgent->ResetDestination();
            s=BH_RUNNING;
            // Obligatorio
            glm::vec3 dest = Singleton<Pathfinding>::Instance()->getRandomNodePosition();
            yo->destino = cTransform->getPosition();
            nvAgent->SetDestination(dest);
            return;
        }
        if(s==BH_RUNNING){
            // Intercambio EL USO DE LOS VECTORES dest y mio
            glm::vec3 dest           = cTransform->getPosition();    // A donde voy
            glm::vec3 mio            = yo->destino;                  // Donde estaba

            ////std::cout << "dest" <<dest<< '\n';
            ////std::cout << "mio" <<mio<< '\n';

            glm::vec3 V_AI_DEST      = dest-mio;
            if(!(dest==mio)){
                V_AI_DEST.y     = 0;
                V_AI_DEST       = glm::normalize(V_AI_DEST);
                V_AI_DEST       = gg::Direccion2D_to_rot(V_AI_DEST);

                cTransform->setRotation(V_AI_DEST);

                yo->destino = cTransform->getPosition();
            }
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
    glm::vec3 mio        = cTransform->getPosition();
    glm::vec3 dest       = yo->destino;
    glm::vec3 direccion  = dest-mio;

    // direccion.y     = 0;
    // direccion       = glm::normalize(direccion);
    // direccion       = gg::Direccion2D_to_rot(direccion);
    //
    // cTransform->setRotation(direccion);
    //
    // direccion       = dest-mio;
    // direccion       = glm::normalize(direccion);
    // cRigidBody->applyConstantVelocity(direccion,MAX_AI_SPEED-(yo->getEnemyType()*VEL_ATENUATION));

    mio.y=0;
    dest.y=0;
    float dist = glm::distance(mio,dest);

    if(dist<min){
        s = BH_SUCCESS;
        //cRigidBody->clearForce();
        cRigidBody->setLinearVelocity(glm::vec3());
        //cRigidBody->applyConstantVelocity(glm::vec3(0,0,0),0);
    }
    else{
        s = BH_RUNNING;
        mio=direccion;
        mio.y     = 0;
        mio       = glm::normalize(mio);
        mio       = gg::Direccion2D_to_rot(mio);

        cTransform->setRotation(mio);

        direccion       = glm::normalize(direccion);
        //cRigidBody->applyConstantVelocity(direccion,yo->getVelocity());
        cRigidBody->applyConstantVelocityNormal(direccion,yo->getVelocity());
        ////std::cout << yo->getVelocity() << '\n';
        //cRigidBody->applyConstantVelocity(direccion,yo->getVelocity());
}


}

void Action::onTerminate(Status state){//tener cuidado de cerrar todos los recursos que abramos
  // //gg::cout("ON TERMINATE: ["+std::to_string(state)+"]");
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
    //gg::cout(yo->getHabilityUpdateCounter());
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
    //gg::cout("SPIT!");
    // yo->spit();
    s = BH_SUCCESS;
}
