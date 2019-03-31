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
#include "ComponentArch/Components/CPlayerController.hpp"

bool        CAIEnem::debugvis=true;
CTransform* CAIEnem::PlayerTransform;
CRigidBody* CAIEnem::PlayerBody;

CAIEnem::CAIEnem(gg::EEnemyType _type, float _agresividad, glm::vec3 _playerPos, bool _playerSeen)
:cTransform(nullptr),cAgent(nullptr), Engine(nullptr),arbol(nullptr), world(nullptr),
 type(_type), agresividad(_agresividad), playerPos(_playerPos), playerSeen(_playerSeen)
{

    SS = Singleton<SoundSystem>::Instance();

    switch (_type) {
        case gg::SOLDIER:
            velocity=2;
            s_caminar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Soldier/SoldierMovimiento", s_caminar);

            s_atacar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Soldier/SoldierAtaque", s_atacar);
            break;
        case gg::TANK:
            velocity=2;
            s_caminar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Tank/TankMovimiento", s_caminar);

            s_atacar = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Tank/TankAtaque_Golpe", s_atacar);

            s_atacar2 = new SonidoNormal();
            SS->createSound("event:/SFX/Enemigos/Tank/TankAtaque_Acido", s_atacar2);
            break;
        case gg::RUSHER:
            velocity=8;

            break;
        case gg::SWARM:

            velocity=1;
            break;
        case gg::TRACKER:
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

    arbol = new Treecontroller(data,type,this);

    Vrange          = 30;
    Arange          = 5;
    enfado          = 1;
    gradovision     = cos(45*3.14159265359/180.f);

    numberOfUpdatesSinceLastHability = 0;

    MHandler_SETPTRS();
}

gg::EMessageStatus CAIEnem::processMessage(const Message &m) {
    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CAIEnem::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, getEntityID()));
    cAgent = static_cast<CAgent*>(Manager->getComponent(gg::AGENT, getEntityID()));
    // nvAgent = static_cast<CNavmeshAgent*>(Manager->getComponent(gg::NAVMESHAGENT,getEntityID()));


    return gg::ST_TRUE;
}

void CAIEnem::Update(){
    enableVisualDebug();
}

void CAIEnem::FixedUpdate(){
    ////std::cout << "entrando" << '\n';

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

    float dist = glm::distance(pTF,cTF_POS);
    if(dist<Vrange){
        // glm::vec3 cTF_ROT    = cTransform->getRotation();
        // glm::vec3 dir        = gg::Direccion2D(cTF_ROT);
        glm::vec3 dir        = cTransform->getRotation() * glm::vec3(0,0,1);
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

        if(dist<Arange){
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
    ////std::cout << "mi pos?" <<playerPos<< '\n';
    ////std::cout << "atacando" <<imAttacking<< '\n';
    arbol->update();
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
    float res = acos(gradovision)*180.f/3.14159265359;

    // glm::vec3 dir    = gg::Direccion2D( cTransform->getRotation());
    // glm::vec3 dir1   = gg::Direccion2D( cTransform->getRotation()+glm::vec3(0,res,0));
    // glm::vec3 dir2   = gg::Direccion2D( cTransform->getRotation()-glm::vec3(0,res,0));

    glm::vec3 dir    = cTransform->getRotation() * glm::vec3(0,0,1);
    glm::vec3 dir1   = cTransform->rotate(res, glm::vec3(0,1,0)) * glm::vec3(0,0,1);
    glm::vec3 dir2   = cTransform->rotate(-res, glm::vec3(0,1,0)) * glm::vec3(0,0,1);



    glm::vec3 inicio = cTransform->getPosition();
    glm::vec3 fin    = dir*Vrange+cTransform->getPosition();
    glm::vec3 fin2   = dir1*Vrange+cTransform->getPosition();
    glm::vec3 fin3   = dir2*Vrange+cTransform->getPosition();

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
    EventSystem->RegisterTriger(kTrig_ExpansiveWave,0,ID,cTransform->getPosition(), 10,50,false,TData());
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
    s_atacar->setParameter("Impacto", 1);
    s_atacar->play();
}
void CAIEnem::playAttack2(){
    s_atacar2->play();
}
