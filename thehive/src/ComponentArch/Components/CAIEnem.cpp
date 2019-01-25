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

CAIEnem::CAIEnem(gg::EEnemyType _type, float _agresividad, gg::Vector3f _playerPos, bool _playerSeen)
:cTransform(nullptr),cAgent(nullptr), Engine(nullptr),arbol(nullptr), world(nullptr),
 type(_type), agresividad(_agresividad), playerPos(_playerPos), playerSeen(_playerSeen)
{
    switch (_type) {
        case gg::SOLDIER:
            velocity=2;
        CanIReset=true;
            break;
        case gg::TANK:
        CanIReset=true;
        velocity=2;
        //velocity=1.75;
            break;
        case gg::RUSHER:
        CanIReset=true;
        velocity=8;
            break;
        case gg::TRACKER:
        CanIReset=true;
        velocity=2;
            break;
    }
}
float CAIEnem::getVelocity(){
    return velocity;
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
    if(!playerOnRange&&CanIReset){
        resetMyOwnTree();
    }
    playerOnRange=true;
}

void CAIEnem::Init(){
    Engine          = Singleton<GameEngine>::Instance();
    Manager         = Singleton<ObjectManager>::Instance();
    EventSystem     = Singleton<CTriggerSystem>::Instance();
    world           = Singleton<ggDynWorld>::Instance();
    data            = new Blackboard();

    playerSeeing        = false;
    playerOnRange       = false;
    //playerSeen          = false;
    ultrasonido         = false;
    senyuelo            = false;
    playerOnRange       = false;
    imAttacking         = false;
    closerAllyIsDead    = false;
    isPlayerAttacking   = false;

    senpos              = gg::Vector3f(50,50,50);
    playerPos           = gg::Vector3f(20,20,20);
    destino             = gg::Vector3f(50,50,50);

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
    //std::cout << "entrando" << '\n';

    if(isPlayerAttacking){
        CClock *clk = static_cast<CClock*>(Manager->getComponent(gg::CLOCK,ID));
        if(clk && clk->hasEnded()){
            isPlayerAttacking = false;
            Manager->removeComponentFromEntity(gg::CLOCK,ID);
        }
    }

    numberOfUpdatesSinceLastHability++;

    gg::Vector3f pTF        = PlayerTransform->getPosition();
    gg::Vector3f cTF_POS    = cTransform->getPosition();

    pTF.Y =0;
    cTF_POS.Y =0;

    float dist = gg::DIST(pTF,cTF_POS);
    if(dist<Vrange){
        gg::Vector3f cTF_ROT    = cTransform->getRotation();
        gg::Vector3f dir        = Direccion2D(cTF_ROT);
        gg::Vector3f diren      = pTF-cTF_POS;

        diren       = gg::Normalice(diren);
        float sol   = gg::Producto(diren,dir);

        if(gradovision<sol){
            //comprobar raytracing
            gg::Vector3f STOESUNUPDATE_PERODEVUELVEUNAPOSICION = world->handleRayCastTo(cTF_POS,pTF,1000);
            int id=world->getIDFromRaycast();
            if(id==Manager->getHeroID()){
                if(!playerSeeing){
                    enemyseen();
                    if(CanIReset){
                        resetMyOwnTree();
                    }
                    resetHabilityUpdateCounter();
                }
            }
            //else if(playerSeeing){
            //    playerSeeing = false;
            //    if(CanIReset){
            //        resetMyOwnTree();
            //    }
            //    resetHabilityUpdateCounter();
            //}

        }

        if(dist<Arange){
            enemyseen();
            enemyrange();
            //arbol->reset();
        }
        else{
            playerOnRange = false;
        }
    }
    else if(playerSeeing){
        playerSeeing = false;
        if(CanIReset){
            resetMyOwnTree();
        }
        resetHabilityUpdateCounter();
    }
    if(playerSeeing){
        playerPos   =PlayerTransform->getPosition();
    }
    //std::cout << "atacando" <<imAttacking<< '\n';
    arbol->update();
}

void CAIEnem::MHandler_ATURD(){
    // std::cout << "aturd" << '\n';
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
    // std::cout << "sen out" << '\n';
    resetMyOwnTree();
}

void CAIEnem::resetMyOwnTree(){
    CNavmeshAgent *nvAgent = static_cast<CNavmeshAgent*>(Manager->getComponent(gg::NAVMESHAGENT,getEntityID()));
    nvAgent->ResetDestination();
    arbol->reset();
}

void CAIEnem::enableVisualDebug(){
    float res = acos(gradovision)*180.f/3.14159265359;

    gg::Vector3f dir    = Direccion2D( cTransform->getRotation());
    gg::Vector3f dir1   = Direccion2D( cTransform->getRotation()+gg::Vector3f(0,res,0));
    gg::Vector3f dir2   = Direccion2D( cTransform->getRotation()-gg::Vector3f(0,res,0));

    gg::Vector3f inicio = cTransform->getPosition();
    gg::Vector3f fin    = dir*Vrange+cTransform->getPosition();
    gg::Vector3f fin2   = dir1*Vrange+cTransform->getPosition();
    gg::Vector3f fin3   = dir2*Vrange+cTransform->getPosition();

    Engine->Draw3DLine(inicio, fin, gg::Color(255,0,0,1),3);
    Engine->Draw3DLine(inicio, fin2, gg::Color(255,0,0,1),3);
    Engine->Draw3DLine(inicio, fin3, gg::Color(255,0,0,1),3);

    gg::Vector3f diren  = PlayerTransform->getPosition()-cTransform->getPosition();
    diren.Y             = 0;
    diren               = gg::Normalice(diren);
    float sol           = gg::Producto(diren,dir);
    gg::Vector3f hola   = Direccion2D_to_rot(dir);
}

void CAIEnem::setPlayerIsAttacking(bool _b){
    isPlayerAttacking = _b;
    playerPos       = PlayerTransform->getPosition();
    playerSeen=true;
    if(CanIReset){
        resetMyOwnTree();
    }
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
        gg::cout(" -- ENFADOMASMAS!!");
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
