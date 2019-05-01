#include "AIDirector.hpp"
//#include "Enum.hpp"
#include <ComponentArch/Components/CFlock.hpp>
#include <BinaryParser.hpp>
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

#define GRADOVISION cos(90*3.14159265359/180.f)
//no se usa
AIDirector::AIDirector (int _id,float _duracion,int _cooldown)
: Manager(nullptr),fac(nullptr)
{
    Manager = Singleton<ObjectManager>::Instance();
    fac = Singleton<Factory>::Instance();
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


    TimeBusqueda=200;
    TimeHorda=50;//300
    TimePico=10;

    AcumulatorBusqueda=0;
    //AcumulatorBusqueda=200;
    AcumulatorHorda=0;
    AcumulatorPico=11;


    canWander=true;
    canHorde=true;

    //Njugador=createNode(glm::vec3(10,3.04,-30.9067),5);
    //std::cout << nodos.size() << '\n';
    //for (size_t i = 0; i < 15; i++) {
    //    auto pos=nodos[i]->getPos();
    //    std::cout << "pos: " <<i<<"(" <<pos.x<<","<<pos.y<<","<<pos.z<<")" <<'\n';
    //}

    Pjugador=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, Manager->getHeroID()));
    camera = static_cast<CCamera*>(Manager->getComponent(gg::CAMERA, Manager->getHeroID()));

    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_1.nav_z", ZONE_1);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_2.nav_z", ZONE_2);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_3.nav_z", ZONE_3);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_4.nav_z", ZONE_4);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_5.nav_z", ZONE_5);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_6.nav_z", ZONE_6);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_7.nav_z", ZONE_7);
}

AIDirector::AIDirector ():AcumulatorBusqueda(0),AcumulatorHorda(0),AcumulatorPico(11),TimeBusqueda(1),TimeHorda(300),TimePico(10),
estres(1),numEnemigos(0),activado(true),canWander(true),canHorde(true),
Pjugador(nullptr),Njugador(nullptr){
    Manager = Singleton<ObjectManager>::Instance();
    fac = Singleton<Factory>::Instance();
    enemigos.reserve(50);
}

AIDirector::~AIDirector (){
    auto it = nodos.begin();
    for(int i=0 ; i<nodos.size() ; ++i){
        delete (*it);
        ++it;
    }

}

AIDirector::AIDirector (const AIDirector &orig){}
void AIDirector::update (float delta){
    if(!activado) return;

    AcumulatorBusqueda += delta;
    //Acumulator+=(delta*(estres/10));
    if(AcumulatorBusqueda > TimeBusqueda){
        //creamos wandering si es necesario
        AcumulatorBusqueda=0;
        //busquedaCerca();
    }
    if(canHorde){
        //std::cout <<"A"<< AcumulatorHorda << '\n';
        AcumulatorHorda += delta;
        if(AcumulatorHorda > TimeHorda){
            //invocamos horda
            AcumulatorHorda=0;
            invocar();
        }
    }
    if(AcumulatorPico<TimePico){
        AcumulatorPico+=delta;
        //invocar especial no se muy bien que hacer
    }
}

void AIDirector::clipingEnemigos(){
    CRenderable_3D* render;
    glm::vec3 cTF_POS    = camera->getCameraPosition();//camara
    cTF_POS.y = 0;
    // glm::vec3 cTF_ROT    = camera->getCameraRotation();
    // glm::vec3 dir        = gg::Direccion2D(cTF_ROT);

    glm::vec3 pTF;
    glm::vec3 diren;

    glm::vec3 dir   = Pjugador->getPosition() - cTF_POS;//esto ya no me vale
    dir = glm::normalize(dir);
    dir.y = 0;

    float sol;

    auto it = enemigos.begin();
    while(it!=enemigos.end()){
        pTF         = (*it)->getPosition(); //Enemigo
        pTF.y       = 0;

        //float dist = gg::DIST(pTF,cTF_POS);
        diren       = pTF-cTF_POS;
        diren       = glm::normalize(diren);
        sol         = glm::dot(diren,dir);
        render  = static_cast<CRenderable_3D*>(Manager->getComponent(gg::RENDERABLE_3D, (*it)->getEntityID()));

        if(GRADOVISION<sol){
            render->setVisibility(true);
        }
        else{
            render->setVisibility(false);
        }
        it++;
    }
}

void AIDirector::comprobar(){
    if(!activado) return;

    int viendome = 0;
    float estresantes = 0, dist;
    glm::vec3 pos = Pjugador->getPosition();
    CTransform* Tenemy;
    CAIEnem* cAIEnem;

    auto it = enemigos.begin();
    while(it!=enemigos.end()){
        //comprobar si me esta atacando
        Tenemy      = *it;
        cAIEnem     = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM, Tenemy->getEntityID()));

        if(cAIEnem && cAIEnem->getPlayerSeeing()){

            viendome++;
            dist = gg::FastDIST(pos, Tenemy->getPosition());
            if(DIST_MIEDO>dist){
                estresantes = estresantes+1-(dist/DIST_MIEDO);
            }
        }
        it++;
    }
    if(!(estresantes==0||viendome==0)){
        estresantes = (estresantes/(viendome+20));//enemigos.size();
        estres = estres + estresantes;
    }

    canHorde? estres = estres-SUBIDARESTA : estres = estres-BAJADARESTA;
    if(estres < 1) estres = 1;

}

void AIDirector::busquedaCerca(){
    float dist  = gg::FastDIST(Njugador->getPos(),Pjugador->getPosition());
    float dist2;

    glm::vec3 posJugador = Pjugador->getPosition();

    auto nodosP = Njugador->nodosProximos;

    auto it = nodosP.begin();
    while(it!=nodosP.end()){
        dist2 =gg::FastDIST((*it)->getPos(),posJugador);
        if(dist<dist2){
            changeNode(*it);
        }
        it++;
    }

}

void AIDirector::changeNode(AINode* nodo){
    auto nodosP     = Njugador->nodosProximos;
    auto nodosTMP   = nodo->nodosProximos;

    auto it         = nodosP.begin();
    auto it2        = nodosTMP.begin();

    while(it != nodosP.end()){
        while(it2 != nodosP.end()){
            if(*it==*it2)       break;
            it2++;
        }

        if(it2!=nodosP.end())   removePos(*it);
        it++;

    }

    while(it2!=nodosP.end()){
        if(!(*it2)->getonRange()){
            if(canWander){
                createWandering(*it2);
            }
            (*it2)->setonRange(true);
        }
        it2++;
    }
    Njugador = nodo;
}

void AIDirector::invocar(){
    //int tam =Njugador->nodosProximos.size()-1;
    //int enemigosint = gg::genIntRandom(0, tam);
    //auto nodo=Njugador->nodosProximos[enemigosint];
    //createHorda(Njugador);

    //esto funciona para todos los nodos
    int tam         = nodos.size()-1;
    int enemigosint = gg::genIntRandom(0, tam);
    auto nodo       = nodos[enemigosint];
    createHorda(nodo);
}

void AIDirector::setActive(bool dato){
    activado=dato;
}

void AIDirector::subida(){}
void AIDirector::pico(){}
void AIDirector::bajada(){}

void AIDirector::createWandering(AINode* nodo){
    CTransform* enemypos;
    glm::vec3 deltapos;

    float rango = nodo->getRange();

    int enemigosint = gg::genIntRandom(MIN_WAN, MAX_WAN);
    int id;

    for (int i = 0; i < enemigosint; i++) {
        deltapos = glm::vec3(gg::genIntRandom(0, 2*rango)-rango,0,gg::genIntRandom(0, 2*rango)-rango);

        id = fac->createSoldierWandering(nodo->getPos()+deltapos, 2000);

        enemypos = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id));
        enemigos.emplace_back(enemypos);
        numEnemigos++;
    }
}

void AIDirector::createHorda(AINode* nodo){


    CTransform* enemypos;
    glm::vec3 dest = Pjugador->getPosition();
    float rango = nodo->getRange();
    int enemigosint = gg::genIntRandom(MIN_WAN, MAX_WAN);

    int id;

    glm::vec3 deltapos;
    glm::vec3 posibuena = nodo->getPos();

    for (int i = 0; i < enemigosint; i++) {
        deltapos = glm::vec3(gg::genIntRandom(0, 2*rango)-rango,0,gg::genIntRandom(0, 2*rango)-rango);

        posibuena = posibuena+deltapos;

        id = fac->createSoldierHorda(nodo->getPos()+deltapos, 10, dest);
        enemypos = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id));
        enemigos.push_back(enemypos);
        numEnemigos++;
    }

}

AINode* AIDirector::createNode(glm::vec3 _pos,float _range){
    auto puntero = new AINode(_pos,_range);
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
    glm::vec3 posicion = nodo->getPos();
    glm::vec3 pos;

    float rango = nodo->getRange();

    auto it = enemigos.begin();
    while(it!=enemigos.end()){
        pos  = (*it)->getPosition();
        pos -= posicion;

        if( abs(pos.x) <= rango && abs(pos.z) <= rango ){
            enemigos.erase(it);
            numEnemigos--;
            Manager->removeEntity((*it)->getEntityID());
        }
        it++;
    }
    nodo->setonRange(false);

}
void AIDirector::invocarswarm(AINode* nodo){
    //std::cout << "nodo" <<nodo->getPos().x<<";"<<nodo->getPos().y<<";"<<nodo->getPos().z<< '\n';

     int id2=fac->createSwarm(nodo->getPos(), 2000);
     //CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
     CFlock* enemyflock=static_cast<CFlock*>(Manager->getComponent(gg::FLOCK, id2));
     auto arr=enemyflock->getFlocked();
     auto it=arr.begin();
     while(it!=arr.end()){
         int id3=(*it)->getEntityID();
         CTransform* enemypos12=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id3));
         enemigos.push_back(enemypos12);//anayadir todo el flock
         it++;
     }

}
void AIDirector::invocartank(AINode* nodo){

    int id2=fac->createTank(nodo->getPos(), 2000);
    CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
    enemigos.push_back(enemypos1);

}
void AIDirector::invocarrusher(AINode* nodo){
    int id2=fac->createRusher(nodo->getPos(), 2000);
    CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
    enemigos.push_back(enemypos1);


}


//codigo de nodo
AINode::AINode(){}
AINode::AINode(glm::vec3 _pos,float _range):pos(_pos),onRange(false),range(_range){}
AINode::AINode(const AINode &orig):pos(orig.pos),onRange(orig.onRange),range(orig.range){}
glm::vec3 AINode::getPos(){
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


// Comenta de aquí pabajo cuando lo tengas todo listo
#include <Omicron/Omicron.hpp>
#include <Singleton.hpp>
void AIDirector::DrawZones(){
    gg::Color color;
    color.Alpha = 1;
    color.R = 60;
    color.G = 216;
    color.B = 32;
    for(uint16_t i = 0; i < ZONE_1.size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_1[i].TL, ZONE_1[i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_1[i].BR, ZONE_1[i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 255;
    color.G = 64;
    color.B = 43;
    for(uint16_t i = 0; i < ZONE_2.size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_2[i].TL, ZONE_2[i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_2[i].BR, ZONE_2[i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 255;
    color.G = 244;
    color.B = 43;
    for(uint16_t i = 0; i < ZONE_3.size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_3[i].TL, ZONE_3[i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_3[i].BR, ZONE_3[i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 230;
    color.G = 43;
    color.B = 255;
    for(uint16_t i = 0; i < ZONE_4.size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_4[i].TL, ZONE_4[i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_4[i].BR, ZONE_4[i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 43;
    color.G = 135;
    color.B = 255;
    for(uint16_t i = 0; i < ZONE_5.size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_5[i].TL, ZONE_5[i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_5[i].BR, ZONE_5[i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 255;
    color.G = 142;
    color.B = 43;
    for(uint16_t i = 0; i < ZONE_6.size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_6[i].TL, ZONE_6[i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_6[i].BR, ZONE_6[i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 43;
    color.G = 244;
    color.B = 255;
    for(uint16_t i = 0; i < ZONE_7.size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_7[i].TL, ZONE_7[i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONE_7[i].BR, ZONE_7[i].BR + glm::vec3(0, 100, 0), color);
    }
};
