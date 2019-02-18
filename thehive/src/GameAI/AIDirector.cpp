#include "AIDirector.hpp"
//#include "Enum.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include <Singleton.hpp>
#include <Factory.hpp>

/*
RECORDATORIO
poner mas nodos
poner y usar medidor de estres:
-Special atacking(Maximun)
depende del estres invocar unas cosas u otras
*/
#define MIN_WAN 7.f
#define MAX_WAN 15.f

//((estres/100)*8)+7;
//((estres/100)*15)+15;

//#define MIN_WAN 15.f
//#define MAX_WAN 30.f


//hordaTime=2;//3-2
//1-(estres/100)


#define DIST_MIEDO 1000.f
#define SUBIDARESTA 0.1f
#define BAJADARESTA 0.3f
//no se usa
AIDirector::AIDirector (int _id,float _duracion,int _cooldown)
: Manager(nullptr),fac(nullptr)
{
    Manager = Singleton<ObjectManager>::Instance();
    fac = Singleton<Factory>::Instance();
    Pjugador=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, Manager->getHeroID()));
    /*
    cargar los puntos de  spawn del mapa
    AINode* AIDirector::createNode(gg::Vector3f _pos,float _range){
    //rellenar node con proximidad y rango

    */
}
void AIDirector::clean(){
    activado=false;
    numEnemigos=0;
    enemigos.clear();

}
void AIDirector::init(){
    activado=true;
    numEnemigos=0;
    estres=1;


    TimeBusqueda=1;
    TimeHorda=300;
    TimePico=10;

    AcumulatorBusqueda=0;
    AcumulatorBusqueda=200;
    AcumulatorHorda=0;
    AcumulatorPico=11;


    canWander=true;
    canHorde=true;
    //Creacion de nodos
    Njugador= createNode(gg::Vector3f(5,3,65),5);
    Njugador->setonRange(true);
    //uint16_t h = sF->createHero(gg::Vector3f(10,3,65),false);
    Pjugador=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, Manager->getHeroID()));


}

AIDirector::AIDirector ():AcumulatorBusqueda(0),AcumulatorHorda(0),AcumulatorPico(11),TimeBusqueda(1),TimeHorda(300),TimePico(10),
estres(1),numEnemigos(0),activado(true),canWander(true),canHorde(true),
Pjugador(nullptr),Njugador(nullptr){
    Manager = Singleton<ObjectManager>::Instance();
    fac = Singleton<Factory>::Instance();
    //Pjugador=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, Manager->getHeroID()));
    //Njugador= createNode(gg::Vector3f(5,3,65),5);



}
AIDirector::~AIDirector (){
    for (size_t i = 0; i < nodos.size(); i++) {
        delete nodos[i];
    }
    //liberamos toda la memoria de los nodos

}

AIDirector::AIDirector (const AIDirector &orig){
}
//tiempo
/*
TimeBusqueda=1;
TimeHorda=300;
TimePico=10;

AcumulatorBusqueda=0;
AcumulatorHorda=0;
AcumulatorPico=0;
*/
void AIDirector::update (float delta){
    if(!activado)return;
    AcumulatorBusqueda+=delta;
    //Acumulator+=(delta*(estres/10));
    TimeBusqueda=200;
    if(AcumulatorBusqueda>TimeBusqueda){
        AcumulatorBusqueda=0;
        //busquedaCerca();
        invocacion(Njugador);
    }
    if(canHorde){
        AcumulatorHorda+=delta;
        if(AcumulatorHorda>AcumulatorHorda){
            AcumulatorHorda=0;
            //invocacion(Njugador);
            //invocar();
        }
    }
    if(AcumulatorPico<TimePico){
        AcumulatorPico+=delta;
        //std::cout << "estoy en pico" << '\n';
        //invocar especial no se muy bien que hacer
    }
    //std::cout << "estres" <<estres<< '\n';
}
void AIDirector::clipingEnemigos(){
    CCamera* camera  = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, Manager->getHeroID()));
    float gradovision     = cos(90*3.14159265359/180.f);
    gg::Vector3f cTF_POS    = camera->getCameraPosition();//camara
    cTF_POS.Y =0;
    gg::Vector3f cTF_ROT    = camera->getCameraRotation();
    gg::Vector3f dir        = Direccion2D(cTF_ROT);


    auto it=enemigos.begin();
    while(it!=enemigos.end()){
        gg::Vector3f pTF        = (*it)->getPosition();//enemigo
        pTF.Y =0;
        //float dist = gg::DIST(pTF,cTF_POS);
        gg::Vector3f diren      = pTF-cTF_POS;
        diren       = gg::Normalice(diren);
        float sol   = gg::Producto(diren,dir);
        CRenderable_3D* render  = static_cast<CRenderable_3D*>(Manager->getComponent(gg::RENDERABLE_3D, (*it)->getEntityID()));
        //if(render){
            if(gradovision<sol){
                render->setVisibility(true);
            }else{
                render->setVisibility(false);
            }
        //}
        it++;
    }
}
void AIDirector::comprobar(){
    if(!activado)return;
    auto it= enemigos.begin();
    int viendome=0;
    float estresantes=0;
    gg::Vector3f pos= Pjugador->getPosition();
    while(it!=enemigos.end()){
        //comprobar si me esta atacando
        CTransform* Tenemy=*it;
        CAIEnem* cAIEnem = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM, Tenemy->getEntityID()));
        if(cAIEnem&&cAIEnem->getPlayerSeeing()){
            viendome++;
            float dist=gg::FastDIST(pos, Tenemy->getPosition());
            if(DIST_MIEDO>dist){
                estresantes=estresantes+1-(dist/DIST_MIEDO);
            }
        }
        it++;
    }
    if(!(estresantes==0||viendome==0)){
        //std::cout << "estresantes" <<estresantes<< '\n';
        //std::cout << "viendome" <<viendome<< '\n';
        estresantes=(estresantes/(viendome+20));//enemigos.size();
        //std::cout << "suma" <<estresantes<< '\n';
        estres =estres+estresantes;
    }
    if(canHorde){
        estres =estres-SUBIDARESTA;
    }
    else{
        estres =estres-BAJADARESTA;
    }
    if(estres<1){
        estres =1;
    }
}



void AIDirector::busquedaCerca(){
    float dist =gg::FastDIST(Njugador->getPos(),Pjugador->getPosition());
    auto it =Njugador->nodosProximos.begin();
    while(it!=Njugador->nodosProximos.end()){
        float dist2 =gg::FastDIST((*it)->getPos(),Pjugador->getPosition());
        if(dist<dist2){
            changeNode(*it);
        }
        it++;
    }

}

void AIDirector::changeNode(AINode* nodo){
    //std::cout << "cambiamos" << '\n';
    auto it =Njugador->nodosProximos.begin();
    while(it!=Njugador->nodosProximos.end()){
        auto it2 =nodo->nodosProximos.begin();
        while(it2!=Njugador->nodosProximos.end()){
            if(*it==*it2){
                break;
            }
            it2++;
        }
        if(it2!=Njugador->nodosProximos.end()){
            removePos(*it);
        }
        it++;

    }
    auto it2 =nodo->nodosProximos.begin();
    while(it2!=Njugador->nodosProximos.end()){
        if(!(*it2)->getonRange()){
            if(canWander){
                createWandering(*it2);
            }
            (*it2)->setonRange(true);
        }
        it2++;
    }
    Njugador=nodo;
}
void AIDirector::invocar(){
    int tam =Njugador->nodosProximos.size()-1;
    int enemigosint = gg::genIntRandom(0, tam);
    auto nodo=Njugador->nodosProximos[enemigosint];
    invocacion(nodo);
}
void AIDirector::invocacion(AINode* nodo){
     createHorda(nodo);
}
void AIDirector::setActive(bool dato){
    activado=dato;
}
void AIDirector::subida(){

}
void AIDirector::pico(){

}
void AIDirector::bajada(){

}
void AIDirector::createWandering(AINode* nodo){
    float rango=nodo->getRange();
    int enemigosint = gg::genIntRandom(MIN_WAN, MAX_WAN);
    for (int i = 0; i < enemigosint; i++) {
        gg::Vector3f deltapos(gg::genIntRandom(0, 2*rango)-rango,0,gg::genIntRandom(0, 2*rango)-rango);

        int id=fac->createSoldierWandering(nodo->getPos()+deltapos, 2000);
        CTransform* enemypos=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id));
        enemigos.push_back(enemypos);
        numEnemigos++;
    }
}
void AIDirector::createHorda(AINode* nodo){

    //gg::Vector3f dest1=Pjugador->getPosition();
    //int id2=fac->createSoldierHorda(nodo->getPos(), 2000,dest1);
    //CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
    //enemigos.push_back(enemypos1);

    //int id2=fac->createRusher(nodo->getPos(), 2000);
    //CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
    //enemigos.push_back(enemypos1);

    //int id2=fac->createTank(nodo->getPos(), 2000);
    //CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
    //enemigos.push_back(enemypos1);

    int id2=fac->createSwarm(nodo->getPos(), 2000);
    //CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
    //enemigos.push_back(enemypos1);//anayadir todo el flock
    CFlock* enemyflock=static_cast<CFlock*>(Manager->getComponent(gg::FLOCK, id2));
    auto arr=enemyflock->getFlocked();
    auto it=arr.begin();
    while(it!=arr.end()){
        int id3=(*it)->getEntityID();
        CTransform* enemypos12=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id3));
        enemigos.push_back(enemypos12);//anayadir todo el flock
        it++;
    }
    return;

    float rango=nodo->getRange();
    gg::Vector3f dest=Pjugador->getPosition();
    int enemigosint = gg::genIntRandom(MIN_WAN, MAX_WAN);
    for (int i = 0; i < enemigosint; i++) {
        gg::Vector3f deltapos(gg::genIntRandom(0, 2*rango)-rango,0,gg::genIntRandom(0, 2*rango)-rango);
        gg::Vector3f posibuena=nodo->getPos();
        posibuena=posibuena+deltapos;
        int id=fac->createSoldierHorda(nodo->getPos()+deltapos, 2000,dest);
        CTransform* enemypos=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id));
        //enemypos->getPosition()
        enemigos.push_back(enemypos);
        numEnemigos++;
    }

}
AINode* AIDirector::createNode(gg::Vector3f _pos,float _range){
    auto puntero=new AINode(_pos,_range);
    nodos.push_back(puntero);
    return puntero;
}
void AIDirector::removeEnemy(CTransform* nodo){
    //enemigos
    auto it=enemigos.begin();
    while(it!=enemigos.end()){
        if(nodo==*it){
            enemigos.erase(it);
            return;
        }
        it++;
    }
}
void AIDirector::removePos(AINode* nodo){
    gg::Vector3f posicion=nodo->getPos();
    auto it= enemigos.begin();
    while(it!=enemigos.end()){
        gg::Vector3f pos = (*it)->getPosition();
        pos-=posicion;
        if(abs(pos.X)<=nodo->getRange()&&abs(pos.Z)<=nodo->getRange()){
            enemigos.erase(it);
            numEnemigos--;
            Manager->removeEntity((*it)->getEntityID());
        }
        it++;
    }
    nodo->setonRange(false);

}
/*
jefe dejamos de invocar
*/

//codigo de nodo
AINode::AINode(){}
AINode::AINode(gg::Vector3f _pos,float _range):pos(_pos),onRange(false),range(_range){}
AINode::AINode(const AINode &orig):pos(orig.pos),onRange(orig.onRange),range(orig.range){}
gg::Vector3f AINode::getPos(){
    return pos;
}
bool AINode::getonRange(){
    return onRange;
}
void  AINode::setonRange(bool nuevo){
    onRange=nuevo;
}
float AINode::getRange(){
    return range;
}
void AINode::addNode(AINode* nuevo){
    //comprobar que esto funciona
    nuevo->nodosProximos.push_back(this);
    nodosProximos.push_back(nuevo);
}
AINode::~AINode(){}
