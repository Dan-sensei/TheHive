#include "AIDirector.hpp"
//#include "Enum.hpp"
#include <ComponentArch/Components/CFlock.hpp>
#include <ComponentArch/Components/CPlayerController.hpp>
#include <BinaryParser.hpp>
#include "PopState.hpp"
#include "States/StateMachine.hpp"

/*
RECORDATORIO
poner y usar medidor de estres:
-Special atacking(Maximun)
depende del estres invocar unas cosas u otras

*/
#define MIN_WAN 3.f
#define MAX_WAN 7.f

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
}

void AIDirector::clean(){
    activado=false;
    numEnemigos=0;
    enemigos.clear();

}

void AIDirector::init(){

    activado=false;
    //activado=true;
    numEnemigos=0;
    estres=1;
    zona_actual=1;

    TimeBusqueda=1;
    TimeHorda=50;//300
    TimePico=10;

    AcumulatorBusqueda=0;
    //AcumulatorBusqueda=200;
    AcumulatorHorda=0;
    AcumulatorPico=11;


    canWander=true;
    canHorde=true;



    Pjugador=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, Manager->getHeroID()));

    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_1.nav_z", ZONAS[0]);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_2.nav_z", ZONAS[1]);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_3.nav_z", ZONAS[2]);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_4.nav_z", ZONAS[3]);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_5.nav_z", ZONAS[4]);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_6.nav_z", ZONAS[5]);
    BinaryParser::ReadNavmeshDataZone("assets/BinaryFiles/NAV/ZONA_7.nav_z", ZONAS[6]);
    //createWandering(1);
    //createWandering(2);
    //checkzone(glm::vec3(0,0,0));
    //invocartank(1);
    //createWandering(1);
}

AIDirector::AIDirector ():AcumulatorBusqueda(0),AcumulatorHorda(0),AcumulatorPico(11),TimeBusqueda(1),TimeHorda(300),TimePico(10),
estres(1),numEnemigos(0),activado(true),canWander(true),canHorde(true),
Pjugador(nullptr){
    Manager = Singleton<ObjectManager>::Instance();
    fac = Singleton<Factory>::Instance();
    enemigos.reserve(50);
}
//que zona send//
int AIDirector::checkzone(glm::vec3 pos){
    int x=pos.x;
    int z=pos.z;
    int sice;

    auto TL=ZONAS[0][0].TL;
    auto BR=ZONAS[0][0].BR;
    glm::vec3 TL_off(-2,0,2);
    glm::vec3 BR_off(2,0,-2);
    for (size_t i = 0; i < 7; i++) {
        sice=ZONAS[i].size();
        ////Director << "tam" <<i<<"="<<sice<< '\n';
        for (size_t e = 0; e < sice; e++) {
            TL=ZONAS[i][e].TL+TL_off;
            BR=ZONAS[i][e].BR+BR_off;
            if(TL.x<x && x<BR.x && BR.z<z && z<TL.z){
                return (i+1);
            }
        }
    }
    return -1;
}
AIDirector::~AIDirector (){
    delete s_vozTantos;

}

AIDirector::AIDirector (const AIDirector &orig){}
void AIDirector::update (float delta){
    if(!activado) return;
    if(muerto){
        AcumulatorHorda=TimeHorda;
        muerto=false;
        //eliminamos enemigos
        removeAllEnem();
        //seleccionamos nueva area de aparacion+ creamos wandering alrededor
        zona_actual-=1;
        if(zona_actual<1){
            zona_actual=1;
        }
        //std::cout << "estamos en " <<zona_actual<< '\n';
        int prev =zona_actual-1;
        if(prev<8 && prev>0){
        //    std::cout << "creamos en :" << prev<<'\n';
            createWandering(prev);
        }
        int post=zona_actual+1;
        if(post<8 && post>0){
        //    std::cout << "creamos en :" << post<<'\n';
            createWandering(post);
        }
        auto pos_jugador=getposzona(zona_actual);
        //CRigidBody* Rjugador=static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, Manager->getHeroID()));
        //Rjugador->setBodyPosition(pos_jugador);
        CPlayerController* cPlayerController=static_cast<CPlayerController*>(Manager->getComponent(gg::PLAYERCONTROLLER, Manager->getHeroID()));
        cPlayerController->reset(pos_jugador);
        //Rjugador->se

        //ponemos pop up muerte

        PopState* aux = new PopState();
        AssetManager* Manager = Singleton<AssetManager>::Instance();
        aux->Addim(Manager->getTextureWithoutSavingToMap("assets/HUD/muerte_esp.png"));
        //estado->Addim(Manager->getTextureWithoutSavingToMap("assets/HUD/camara_esp.png"));
        Singleton<StateMachine>::Instance()->AddState(aux);

        return;
    }

    AcumulatorBusqueda += delta;
    //Acumulator+=(delta*(estres/10));
    if(AcumulatorBusqueda > TimeBusqueda){
        //creamos wandering si es necesario
        comprobar();
        AcumulatorBusqueda=0;
        busquedaCerca();
    }
    if(canHorde){
        ////Director <<"A"<< AcumulatorHorda << '\n';
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
//funcion comprieba si hemos cambiado de zona
void AIDirector::busquedaCerca(){
    ////Director << "buscamos cerca" << '\n';
    int zona = checkzone(Pjugador->getPosition());
    if(zona!=-1 && zona_actual!=zona){
        changeNode(zona);
    }
    if(zona!=-1 ){
        ////Director << "zona: " <<zona<< '\n';
    }
}
//cambiamos de zona
void AIDirector::changeNode(int nodo){
    int dif=nodo -zona_actual;

    int crear=nodo +dif;
    int destruir=zona_actual-dif;
    zona_actual=nodo;
    //std::cout << "cambiamos" <<nodo<< '\n';
    if(crear>0 && crear<8){
    //    std::cout << "creamos" <<crear<< '\n';
        createWandering(crear);
    }
    ////Director << "destruimos" <<destruir<< '\n';
    if(destruir>0 && destruir<8){
    //    std::cout << "destruimos" <<destruir<< '\n';
        removePos(destruir);
    }
}
//sacamos pos aleatoria de una zona
glm::vec3 AIDirector::getposzona(int nodo){
    //Director << "get pos" <<nodo<< '\n';
    if(nodo==-1){
        nodo=gg::genIntRandom(1, 7);
    }
    //Director << "llega" <<ZONAS[nodo-1].size()<< '\n';
    int rand=gg::genIntRandom(0, ZONAS[nodo-1].size()-1);
    //Director << "llega" <<rand<< '\n';

    SimpleFace posbuena=ZONAS[nodo-1][rand];
    //Director << "llega" << '\n';
    float xmenos=posbuena.TL.x;
    float xmas  =posbuena.BR.x;
    float y     =posbuena.BR.y + 20;
    float zmenos=posbuena.BR.z;
    float zmas  =posbuena.TL.z;
    //Director << "llegax" << '\n';

    float dx=xmas-xmenos;
    float dz=zmas-zmenos;

    glm::vec3 res=glm::vec3(xmenos+gg::genFloatRandom(0, dx),y,zmenos+gg::genFloatRandom(0, dz));
    ////Director << "res (" <<res.x<<","<<res.y<<","<<res.z<<")"<< '\n';
    return res;


}

//creamos horda delante o atras
void AIDirector::invocar(){
    int enemigosint =0;
    if(zona_actual<6&&zona_actual>2){
        enemigosint = gg::genIntRandom(0, 2);
    }else if(zona_actual>=6){
        enemigosint=1;

    }
    int nodo=0;
    if(enemigosint==0){
        if(zona_actual==2){

            nodo=zona_actual+3;
        }
        else{
            nodo=zona_actual+2;

        }
    }
    else{

        nodo=zona_actual-2;
    }

    //std::cout << "invocar :" <<zona_actual<< '\n';
    //std::cout << "invocar ::" <<nodo<< '\n';
    //esto funciona para todos los nodos
    createHorda(nodo);
}

void AIDirector::setActive(bool dato){
    //Director << "entra2" << '\n';
    activado=dato;
    if(activado){
        //Director << "entra3" << '\n';

        //sonido de donde salen tantos
        // SS = Singleton<SoundSystem>::Instance();
        // s_vozTantos= new SonidoNormal();
        // SS->createSound("event:/Voces/Jugador/FraseSoldier2", s_vozTantos);
        // s_vozTantos->play();

        createWandering(1);
        createWandering(2);
        //invocartank(1);
        //invocarswarm(1);
        //invocarrusher(1);
    }
    //Director << "entra4" << '\n';
}

void AIDirector::subida(){}
void AIDirector::pico(){}
void AIDirector::bajada(){}

void AIDirector::createWandering(int nodo){

    //Director << "creamos en zona:" <<nodo<< '\n';
    CTransform* enemypos;
    glm::vec3 zonarand;
    int enemigosint = gg::genIntRandom(MIN_WAN, MAX_WAN);
    //int enemigosint = 1;
    int id;

    for (int i = 0; i < enemigosint; i++) {
        //zonarand=navmesh punto zona
        zonarand=getposzona(nodo);
        id = fac->createSoldierWandering(zonarand, 1);

        enemypos = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id));
        enemigos.emplace_back(enemypos);
        numEnemigos++;
    }
}

void AIDirector::createHorda(int nodo){

    glm::vec3 dest = Pjugador->getPosition();

    CTransform* enemypos;
    glm::vec3 zonarand;
    int enemigosint = gg::genIntRandom(MIN_WAN, MAX_WAN);
    int id;


    for (int i = 0; i < enemigosint; i++) {
        zonarand=getposzona(nodo);
        id = fac->createSoldierHorda(zonarand, 1, dest);

        enemypos = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id));
        enemigos.push_back(enemypos);
        numEnemigos++;
    }

}



void AIDirector::removeEnemy(CTransform* nodo){
    //enemigos
    auto it=enemigos.begin();
    while(it!=enemigos.end()){
        if(nodo==*it){
            enemigos.erase(it);
            numEnemigos--;
            return;
        }
        it++;
    }
}
void AIDirector::restart(){
    //removeAllEnem();
    //std::cout << "eliminado" << '\n';
    //activado=false;
    muerto=true;

}
void AIDirector::removeAllEnem(){
    auto it=enemigos.begin();
    while(it!=enemigos.end()){
            int id=(*it)->getEntityID();
            Manager->removeEntity(id);
            it++;
    }
    enemigos.clear();
    numEnemigos=0;
}
//eliminamos todos los enemigos de una zona
void AIDirector::removePos(int nodo){



    int zona;
    auto it=enemigos.begin();
    while(it!=enemigos.end()){
        zona = checkzone((*it)->getPosition());
        if(zona!=-1 && nodo==zona){
            ////Director << "eliminamos enemigo" << '\n';
            //changeNode(zona);
            int id=(*it)->getEntityID();
            enemigos.erase(it);
            numEnemigos--;
            Manager->removeEntity(id);
        }
        else{
            it++;

        }
    }
}

void AIDirector::invocarswarm(int nodo){
    ////Director << "nodo" <<nodo->getPos().x<<";"<<nodo->getPos().y<<";"<<nodo->getPos().z<< '\n';
    glm::vec3 zonarand=getposzona(nodo);

     int id2=fac->createSwarm(zonarand, 0.1);
     //CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
     CFlock* enemyflock=static_cast<CFlock*>(Manager->getComponent(gg::FLOCK, id2));
     auto arr=enemyflock->getFlocked();
     auto it=arr.begin();
     while(it!=arr.end()){
         int id3=(*it)->getEntityID();
         CTransform* enemypos12=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id3));
         enemigos.push_back(enemypos12);//anayadir todo el flock
         numEnemigos++;
         it++;
     }

}

void AIDirector::invocartank(int nodo){


    //glm::vec3 dest = Pjugador->getPosition();

        glm::vec3 zonarand=getposzona(nodo);
        int id2=fac->createTank(zonarand, 5);
        CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
        enemigos.push_back(enemypos1);
        numEnemigos++;

}
void AIDirector::invocarrusher(int nodo){

    //glm::vec3 zonarand=getposzona(nodo);
    glm::vec3 zonarand=glm::vec3(0,0,0);
    int id2=fac->createRusher(zonarand, 2);
    //CTransform* enemypos1=static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, id2));
    //enemigos.push_back(enemypos1);
    //numEnemigos++;


}






// Comenta de aquí pabajo cuando lo tengas todo listo
#include <Omicron/Omicron.hpp>
#include <Singleton.hpp>
void AIDirector::DrawZones(){
    gg::Color color;
    color.Alpha = 1;
    color.R = 60;
    color.G = 216;
    color.B = 32;
    for(uint16_t i = 0; i < ZONAS[0].size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[0][i].TL, ZONAS[0][i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[0][i].BR, ZONAS[0][i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 255;
    color.G = 64;
    color.B = 43;
    for(uint16_t i = 0; i < ZONAS[1].size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[1][i].TL, ZONAS[1][i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[1][i].BR, ZONAS[1][i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 255;
    color.G = 244;
    color.B = 43;
    for(uint16_t i = 0; i < ZONAS[2].size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[2][i].TL, ZONAS[2][i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[2][i].BR, ZONAS[2][i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 230;
    color.G = 43;
    color.B = 255;
    for(uint16_t i = 0; i < ZONAS[3].size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[3][i].TL, ZONAS[3][i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[3][i].BR, ZONAS[3][i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 43;
    color.G = 135;
    color.B = 255;
    for(uint16_t i = 0; i < ZONAS[4].size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[4][i].TL, ZONAS[4][i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[4][i].BR, ZONAS[4][i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 255;
    color.G = 142;
    color.B = 43;
    for(uint16_t i = 0; i < ZONAS[5].size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[5][i].TL, ZONAS[5][i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[5][i].BR, ZONAS[5][i].BR + glm::vec3(0, 100, 0), color);
    }
    color.R = 43;
    color.G = 244;
    color.B = 255;
    for(uint16_t i = 0; i < ZONAS[6].size(); ++i){
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[6][i].TL, ZONAS[6][i].TL + glm::vec3(0, 100, 0), color);
        Singleton<Omicron>::Instance()->Draw3DLine(ZONAS[6][i].BR, ZONAS[6][i].BR + glm::vec3(0, 100, 0), color);
    }
};
