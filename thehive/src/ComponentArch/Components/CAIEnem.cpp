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

bool        CAIEnem::debugvis=true;
CTransform* CAIEnem::PlayerTransform;

CAIEnem::CAIEnem(gg::EEnemyType _type, float _agresividad, gg::Vector3f _playerPos, bool _playerSeen)
:cTransform(nullptr),cAgent(nullptr), Engine(nullptr),arbol(nullptr),
 type(_type), agresividad(_agresividad), playerPos(_playerPos), playerSeen(_playerSeen)
{
    // void* a la estructura inicializadora para acceder a los elementos
}
void CAIEnem::setSigno(int _signo){
    signo=_signo;
}
int CAIEnem::getSigno(){
    return signo;
}
CAIEnem::~CAIEnem() {
    delete arbol;
}

void CAIEnem::enemyseen(){
    playerPos   =PlayerTransform->getPosition();
    playerSeen  =true;
    playerSeeing=true;
}

void CAIEnem::enemyrange(){
    playerOnRange=true;
}

void CAIEnem::Init(){
    Engine = Singleton<GameEngine>::Instance();
    Manager = Singleton<ObjectManager>::Instance();
    data= new Blackboard();
    //int id_dado=getEntityID();
    //// std::cout << "id dado:" <<id_dado<< '\n';

    playerSeeing    = false;
    playerOnRange   = false;
    //playerSeen      = false;
    ultrasonido     = false;
    senyuelo        = false;
    playerOnRange   = false;
    imAttacking     = false;

    senpos          = gg::Vector3f(50,50,50);
    //playerPos       = gg::Vector3f(20,20,20);
    destino         = gg::Vector3f(50,50,50);

    id              = getEntityID();
    id2             = PlayerTransform->getEntityID();
    ultrasonido_cont= 0;
    rondacion_cont  = 0;
    signo=1;

    data->setData("id2",new BInt(id2));

    //data->serData()
    //// std::cout << "arbol1" << '\n';
    //// std::cout << "creado" << '\n';
    arbol = new Treecontroller(data,0,this);
    //// std::cout << "creadowii" << '\n';

    //// std::cout << "arbol2" << '\n';
    Vrange          = 30;
    Arange          = 2;
    enfado          = 1;
    gradovision     = cos(30*3.14159265359/180.f);

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

    return gg::ST_TRUE;
}

void CAIEnem::Update(){
    //std::cout << "entrando" << '\n';
    if(debugvis)  enableVisualDebug();

    CClock *clk = static_cast<CClock*>(Manager->getComponent(gg::CLOCK,id));
    if(clk && clk->hasEnded()){
        isPlayerAttacking = false;
        Manager->removeComponentFromEntity(gg::CLOCK,id);
    }

    gg::Vector3f pTF        = PlayerTransform->getPosition();
    gg::Vector3f cTF_POS    = cTransform->getPosition();
    float dist = gg::DIST(pTF,cTF_POS);
    if(dist<Vrange){
        gg::Vector3f cTF_ROT    = cTransform->getRotation();
        gg::Vector3f dir        = Direccion2D(cTF_ROT);
        gg::Vector3f diren      = pTF-cTF_POS;


        diren.Y     = 0;
        diren       = gg::Normalice(diren);
        float sol   = gg::Producto(diren,dir);

        if(gradovision<sol && !playerSeeing){
            enemyseen();
            arbol->reset();
        }

        if(dist<Arange && !playerOnRange){
            enemyrange();
        }
        else if(playerOnRange){
            playerOnRange = false;
        }
    }
    else if(playerSeeing){
        playerSeeing = false;
        arbol->reset();
    }
    arbol->update();
}

void CAIEnem::MHandler_ATURD(){
    // std::cout << "aturd" << '\n';
    ultrasonido     = true;
    ultrasonido_cont= 0;
    arbol->reset();

}

void CAIEnem::MHandler_NEAR(TriggerRecordStruct* cdata){

}

void CAIEnem::MHandler_SENYUELO(TriggerRecordStruct* cdata){
    senyuelo    = true;
    senpos      = cdata->vPos;
    arbol->reset();
    // std::cout << "sen in" << '\n';
}

void CAIEnem::MHandler_SENYUELO_END(){
    senyuelo    = false;
    // std::cout << "sen out" << '\n';
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

    CClock *clk = static_cast<CClock*>(Manager->getComponent(gg::CLOCK,id));
    if(clk){
        clk->restart();
    }
    else{
        clk = new CClock();
        clk->startChrono(3000);
        Manager->addComponentToEntity(clk,gg::CLOCK,id);
    }
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
