#include "CAIEnem.hpp"

#include <list>
#include "ComponentArch/Message.hpp"

#include <Util.hpp>

#include "CAgent.hpp"
#include "CTransform.hpp"

#include "EventSystem/Blackboard.hpp"
#include "EventSystem/BData.hpp"
#include "EventSystem/BInt.hpp"
#include "EventSystem/BFloat.hpp"
#include "EventSystem/BVector3f.hpp"
#include "EventSystem/BBool.hpp"
#include "Singleton.hpp"
#include "GameAI/AIDirector.hpp"
#include "ComponentArch/Components/CPlayerController.hpp"

#include <ComponentArch/Components/CRigidBody.hpp>
#include <ComponentArch/Components/CNavmeshAgent.hpp>

bool        CAIEnem::debugvis=true;
CTransform* CAIEnem::PlayerTransform;
CRigidBody* CAIEnem::PlayerBody;

CAIEnem::CAIEnem(gg::EEnemyType _type, float _agresividad, glm::vec3 _playerPos, bool _playerSeen)
:cTransform(nullptr),cAgent(nullptr), Engine(nullptr),arbol(nullptr), world(nullptr),
 type(_type), agresividad(_agresividad), playerPos(_playerPos), playerSeen(_playerSeen),ghostCollider(nullptr)
{

    SS = Singleton<SoundSystem>::Instance();

    switch (_type) {
        case gg::SOLDIER:
        Arange          = 1;

            velocity=2;
            s_caminar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Soldier/SoldierMovimiento", s_caminar);

            s_atacar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Soldier/SoldierAtaque", s_atacar);

            s_grito = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Soldier/SoldierGrito", s_grito);
            break;
        case gg::TANK:
        Arange          = 2;

            velocity=1;
            s_caminar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Tank/TankMovimiento", s_caminar);

            s_atacar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Tank/TankAtaque", s_atacar);

            s_grito = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Tank/TankGrito", s_grito);

            break;
        case gg::RUSHER:
        Arange          = 1;

            velocity=8;

            s_caminar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Rusher/RusherDash", s_caminar);

            s_atacar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Rusher/RusherCarga", s_atacar);

            s_grito = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Rusher/RusherGrito", s_grito);


            break;
        case gg::SWARM:
        Arange          = 1;


            velocity=1;

            s_caminar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Swarm/SwarmMovimiento", s_caminar);

            s_atacar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Swarm/SwarmAtaque", s_atacar);

            s_grito = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Swarm/SwarmGrito", s_grito);

            break;
        case gg::TRACKER:
        Arange          = 1;

        velocity=2;
            break;
    }
}
float CAIEnem::getVelocity(){
    return velocity;
}
bool CAIEnem::getPlayerSeeing(){
    return playerSeeing;
}
void CAIEnem::setSigno(int _signo){
    signo=_signo;
}

int CAIEnem::getSigno(){
    return signo;
}

CAIEnem::~CAIEnem() {
    delete s_caminar;
    delete s_atacar;
    delete s_grito;

    delete collider;

    //CPlayerController::
    //CPlayerController::cont_enemigos--;
    delete arbol;
}

void CAIEnem::enemyseen(){
    playerPos       = PlayerTransform->getPosition();
    playerSeen      = true;
    playerSeeing    = true;
}


void CAIEnem::enemyrange(){
    playerOnRange=true;
}

void CAIEnem::Init(){
    Engine          = Singleton<Omicron>::Instance();
    Manager         = Singleton<ObjectManager>::Instance();
    EventSystem     = Singleton<CTriggerSystem>::Instance();
    world           = Singleton<ggDynWorld>::Instance();
    data            = new Blackboard();
    PlayerTransform = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM,Manager->getHeroID()));
    PlayerBody = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,Manager->getHeroID()));

    MHandler_SETPTRS();

    cDynamicModel = static_cast<CDynamicModel*>(Manager->getComponent(gg::DYNAMICMODEL, getEntityID()));
    cDynamicModel->setStepDistance(0.8f);
    playerSeeing        = false;
    playerOnRange       = false;
    //playerSeen          = false;
    ultrasonido         = false;
    senyuelo            = false;
    playerOnRange       = false;
    imAttacking         = false;
    closerAllyIsDead    = false;
    isPlayerAttacking   = false;

    senpos              = glm::vec3(50,50,50);
    //playerPos           = glm::vec3(20,20,20);
    destino             = glm::vec3(50,50,50);

    ID                  = getEntityID();
    ultrasonido_cont    = 0;
    rondacion_cont      = 0;
    signo               = 1;
    maxAliensAttacking  = 2;

    zona=-2;

    arbol = new Treecontroller(data,type,this);

    Vrange          = 20;
    //Arange          = 1;
    enfado          = 1;
    gradovision     = cos(180.f*3.14159265359/180.f);

    numberOfUpdatesSinceLastHability = 0;

    // -----------------------------
    ghostCollider = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,getEntityID()));
    glm::vec3 c_pos = ghostCollider->getBodyPosition();
    collider = new CRigidBody(false, false,"", c_pos.x,c_pos.y,c_pos.z, 0.2,0.2,0.2, 50, 0,0,0);
    collider->deactivateGravity();

    GH_PREV = glm::vec3(0);
    isColliderGravitySet = true;
    // -----------------------------

}

gg::EMessageStatus CAIEnem::processMessage(const Message &m) {
    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
float CAIEnem::getArange(){
    return Arange;
}
gg::EMessageStatus CAIEnem::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, getEntityID()));
    cAgent = static_cast<CAgent*>(Manager->getComponent(gg::AGENT, getEntityID()));
    //

    // nvAgent = static_cast<CNavmeshAgent*>(Manager->getComponent(gg::NAVMESHAGENT,getEntityID()));
    //std::cout << " res" <<res<< '\n';
    checkzona();

    return gg::ST_TRUE;
}

void CAIEnem::checkzona(){
    auto res=Singleton<AIDirector>::Instance()->checkzone(cTransform->getPosition());
    if(res!=-1){
        zona=res;
    }
    //std::cout << " res" <<res<< '\n';


}

void CAIEnem::Update(){
    // enableVisualDebug();
}

void CAIEnem::FixedUpdate(){
    ////std::cout << "entrando" << '\n';
    checkzona();

    if(isPlayerAttacking){
        CClock *clk = static_cast<CClock*>(Manager->getComponent(gg::CLOCK,ID));
        if(clk && clk->hasEnded()){
            isPlayerAttacking = false;
            Manager->removeComponentFromEntity(gg::CLOCK,ID);
        }
    }

    numberOfUpdatesSinceLastHability++;

    glm::vec3 pTF        = PlayerTransform->getPosition();
    glm::vec3 cTF_POS    = cTransform->getPosition();

    pTF.y =0;
    cTF_POS.y =0;
    if(playerSeeing){
        glm::vec3 diren      = pTF-cTF_POS;
        diren       = glm::normalize(diren);
        diren       = gg::Direccion2D_to_rot(diren);

        //cTransform->setRotation(V_AI_DEST);
        ghostCollider->setRotY(180+diren.y);

    }

    float dist = glm::distance(pTF,cTF_POS);
    if(dist<15){
        if(!s_caminar->isPlaying()){
            s_caminar->setPosition(cTF_POS);
            s_caminar->play();
        }

        int ramstein=gg::genIntRandom(1, 500);
        if(ramstein==66){
            s_grito->setPosition(cTF_POS);
            s_grito->play();
        }

    }
    else{
        if(s_caminar->isPlaying()){
            s_caminar->stop_fadeout();
        }
    }
    if(dist<Vrange){
        // glm::vec3 cTF_ROT    = cTransform->getRotation();
        // glm::vec3 dir        = gg::Direccion2D(cTF_ROT);
        glm::vec3 dir        = cTransform->getRotation() * glm::vec3(0,0,1);
        dir *=-1;
        glm::vec3 diren      = pTF-cTF_POS;

        diren       = glm::normalize(diren);
        float sol   = glm::dot(diren,dir);

        if(gradovision<sol){
            //comprobar raytracing
            //CRigidBody* body = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,Manager->getHeroID()));
            //glm::vec3 posmala        = PlayerBody->getBodyPosition();


            glm::vec3 STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCastTo(cTransform->getPosition(),PlayerBody->getBodyPosition(),Vrange);
            int id=world->getIDFromRaycast();
            if(id==Manager->getHeroID()){
                //lo veo
                playerSeen      = true;
                playerSeeing    = true;
                playerPos       = PlayerTransform->getPosition();

                //resetHabilityUpdateCounter();
            }
            else if(playerSeeing){
            CAIEnem* cAIEnem =  static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,getEntityID()));
            if(cAIEnem&&cAIEnem->playerSeeing){

            }
            }else{
                //no lo veo
                playerSeeing = false;
                //playerSeen = true;
                resetHabilityUpdateCounter();
            }
        }
        else if(playerSeeing){
            //no lo veo
            playerSeeing = false;
            //playerSeen = true;
            resetHabilityUpdateCounter();
        }

        if((dist-0.1)<=Arange){
            //lo tengo encima
            playerSeen      = true;
            playerSeeing    = true;
            playerOnRange   =  true;
            playerPos       = PlayerTransform->getPosition();

        }
        else{
            //no lo tengo encima
            playerOnRange = false;
        }
    }
    //if(playerSeeing){
    //    playerPos       = PlayerTransform->getPosition();

    //}
    ////std::cout << "mi pos?" <<playerPos;
    ////std::cout << "atacando" <<imAttacking;
    arbol->update();

    if(cDynamicModel->getCurrentAnimation() != A_ENEMIES::E_WALKING && cDynamicModel->getAnimationPlayed()){
        cDynamicModel->ToggleAnimation(A_ENEMIES::E_WALKING, 0.4, false);
    }
}

void CAIEnem::moveBodies(const glm::vec3 &vel){
    collider->activate(true);
    collider->setLinearVelocity(vel);

    glm::vec3 tmp = collider->getBodyPosition();
    ghostCollider->setBodyPosition(tmp);

    // Auto-stepping
    #define RC_OFFSET           1.6f                // Max offset del auto-stepping
    glm::vec3 start = ghostCollider->getBodyPosition();
    glm::vec3 end = glm::vec3(start.x,start.y-(RC_OFFSET),start.z);
    glm::vec3 result;

    bool hit = world->RayCastTest(start,end,result,ghostCollider,collider);

    if(hit){
        result.y += RC_OFFSET/1.7f;
        ghostCollider->setBodyPosition(result);

        start = collider->getLinearVelocity();

        collider->deactivateGravity();
        collider->setLinearVelocity(glm::vec3(start.x,0,start.z));

        if(isColliderGravitySet || GH_PREV != result){
            result.y += 0.3;
            collider->setNotKinematicBodyPosition(result);
            isColliderGravitySet = false;
            GH_PREV = result;
        }
    }
    else{
        collider->activateGravity();
        isColliderGravitySet = true;
        GH_PREV = glm::vec3(0);
    }
}

void CAIEnem::MHandler_ATURD(){
    // //std::cout << "aturd" << '\n';
    ultrasonido     = true;
    ultrasonido_cont= 0;
    resetMyOwnTree();
}

void CAIEnem::MHandler_SENYUELO(TriggerRecordStruct* cdata){
    senyuelo    = true;
    senpos      = cdata->vPos;
    resetMyOwnTree();
}

void CAIEnem::MHandler_SENYUELO_END(){
    senyuelo    = false;
    // //std::cout << "sen out" << '\n';
    resetMyOwnTree();
}

void CAIEnem::resetMyOwnTree(){
    CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(Manager->getComponent(gg::NAVMESHAGENT,getEntityID()));
    nvAgent->ResetDestination();
    arbol->reset();
}

void CAIEnem::enableVisualDebug(){
    //std::cout << "entra" << '\n';




    float res = acos(gradovision)*180.f/3.14159265359;

    // glm::vec3 dir    = gg::Direccion2D( cTransform->getRotation());
    // glm::vec3 dir1   = gg::Direccion2D( cTransform->getRotation()+glm::vec3(0,res,0));
    // glm::vec3 dir2   = gg::Direccion2D( cTransform->getRotation()-glm::vec3(0,res,0));



    glm::vec3 dir    = cTransform->getRotation() * glm::vec3(0,0,1);
    dir *=-1;
    glm::vec3 dir1   = cTransform->rotate(res, glm::vec3(0,1,0)) * glm::vec3(0,0,1);
    dir1 *=-1;
    cTransform->rotate(-res, glm::vec3(0,1,0));
    glm::vec3 dir2   = cTransform->rotate(-res, glm::vec3(0,1,0)) * glm::vec3(0,0,1);
    dir2 *=-1;
    cTransform->rotate(res, glm::vec3(0,1,0));


    glm::vec3 inicio = cTransform->getPosition();
    glm::vec3 fin    = dir*Vrange+inicio;
    glm::vec3 fin2   = dir1*Vrange+inicio;
    glm::vec3 fin3   = dir2*Vrange+inicio;

    Engine->Draw3DLine(inicio, fin, gg::Color(255,0,0,1));
    Engine->Draw3DLine(inicio, fin2, gg::Color(255,0,0,1));
    Engine->Draw3DLine(inicio, fin3, gg::Color(255,0,0,1));

    glm::vec3 diren  = PlayerTransform->getPosition()-cTransform->getPosition();
    diren.y             = 0;
    diren               = glm::normalize(diren);
    float sol           = glm::dot(diren,dir);
    glm::vec3 hola   = gg::Direccion2D_to_rot(dir);
}

void CAIEnem::setPlayerIsAttacking(bool _b){
    isPlayerAttacking = _b;
    playerPos       = PlayerTransform->getPosition();
    playerSeen=true;
    //resetMyOwnTree();
    CClock *clk = static_cast<CClock*>(Manager->getComponent(gg::CLOCK,ID));
    if(clk){
        clk->restart();
    }
    else{
        clk = new CClock();
        clk->startChrono(3000);
        Manager->addComponentToEntity(clk,gg::CLOCK,ID);
    }
}

void CAIEnem::explosiveWave(){
    // TODO
    //EventSystem
    TData mes;
    mes.add(kDat_Damage,10000);
    //mes.add(kDat_img1,0);
    //std::cout << "entra" << '\n';

    //EventSystem->RegisterTriger(kTrig_ExpansiveWave,0,ID,cTransform->getPosition(), 10,50,false,mes);
    EventSystem->PulsoTrigger(kTrig_ExpansiveWave,ID,cTransform->getPosition(),50,mes);
}

bool CAIEnem::getPlayerIsAttacking(){
    return isPlayerAttacking;
}

void CAIEnem::setCloserAllyIsDead(bool _b){
    closerAllyIsDead = _b;
}

bool CAIEnem::getCloserAllyIsDead(){
    return closerAllyIsDead;
}

void CAIEnem::upgradeRage(){
    enfado++;
    if(enfado >= 3){
        //gg::cout(" -- ENFADOMASMAS!!");
        maxAliensAttacking++;
        enfado = 1;
    }
}

float CAIEnem::getRage(){
    return enfado;
}

void CAIEnem::setImAttacking(bool _b){
    imAttacking = _b;
}

bool CAIEnem::getImAttacking(){
    return imAttacking;
}

void CAIEnem::resetHabilityUpdateCounter(){
    numberOfUpdatesSinceLastHability = 0;
}

int CAIEnem::getHabilityUpdateCounter(){
    return numberOfUpdatesSinceLastHability;
}

int CAIEnem::getEnemyType(){
    return type;
}

void CAIEnem::upgradeMaxAliensAttackingAtOnce(){
    maxAliensAttacking++;
}
int CAIEnem::getMaxAliensAttackingAtOnce(){
    return maxAliensAttacking;
}

void CAIEnem::playMovement(){
    s_caminar->play();
}
void CAIEnem::playAttack(){
    if(cDynamicModel->getCurrentAnimation() != A_ENEMIES::E_ATTACKING){
        cDynamicModel->ToggleAnimation(A_ENEMIES::E_ATTACKING, 0.3);
    }
    s_atacar->setParameter("Impacto", 1);
    s_atacar->play();
}
void CAIEnem::playAttack2(){
    if(cDynamicModel->getCurrentAnimation() != A_ENEMIES::E_ATTACKING){
        cDynamicModel->ToggleAnimation(A_ENEMIES::E_ATTACKING, 0.3);
    }
    s_atacar->setParameter("Impacto", 0);
    s_atacar->play();
    // s_atacar2->play();
}
