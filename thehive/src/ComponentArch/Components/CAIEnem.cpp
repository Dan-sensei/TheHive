#include "CAIEnem.hpp"
#include "ComponentArch/Components/CAIEnem.hpp"

#include <list>
#include "ComponentArch/Message.hpp"

//#include <BT/RandomSelector.hpp>
//#include <BT/RandomSequence.hpp>
//#include <BT/Action.hpp>
//#include <BT/Sequence.hpp>
//#include <BT/Selector.hpp>
#include <Util.hpp>

#include "CAgent.hpp"
#include "CTransform.hpp"

#include "EventSystem/Blackboard.hpp"
#include "EventSystem/BData.hpp"
#include "EventSystem/BInt.hpp"
#include "EventSystem/BFloat.hpp"
#include "EventSystem/BVector3f.hpp"
#include "EventSystem/BBool.hpp"


//std::list  <TriggerRecordStruct*>  hola;




//CAIEnem::CAIEnem(unsigned long _dwTriggerFlags,gg::Vector3f _vPos){
//    nCAIEnemID=id2;
//    id2++;
//    dwTriggerFlags=_dwTriggerFlags;
//    nDeltaTime=0;
//    vPos=_vPos;
//}
CTransform* CAIEnem::PlayerTransform;     //  Punteros a otras componentes


CAIEnem::CAIEnem(gg::EEnemyType _type, float _agresividad, gg::Vector3f _playerPos, bool _playerSeen)
:cTransform(nullptr),cAgent(nullptr), Engine(nullptr),arbol(nullptr),
 type(_type), agresividad(_agresividad), playerPos(_playerPos), playerSeen(_playerSeen)
{
    // void* a la estructura inicializadora para acceder a los elementos
}

CAIEnem::~CAIEnem() {
    delete arbol;
}
void CAIEnem::enemyseen(){
//
playerPos=PlayerTransform->getPosition();
playerSeen=true;
playerSeeing=true;
//
}
void CAIEnem::enemyrange(){
playerOnRange=true;
}

void CAIEnem::initComponent() {
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::AIENEM, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::AIENEM, gg::M_SETPTRS);


}

void CAIEnem::Init(){
    enfado=0;
    Engine = Singleton<GameEngine>::Instance();
    data= new Blackboard();
    //int id_dado=getEntityID();
    //// std::cout << "id dado:" <<id_dado<< '\n';

    playerSeeing=false;
    playerOnRange=false;
    playerSeen=false;
    ultrasonido=false;
    senyuelo=false;
    senpos=gg::Vector3f(50,50,50);
    playerPos=gg::Vector3f(20,20,20);
    destino=gg::Vector3f(50,50,50);
    id=getEntityID();
    id2=PlayerTransform->getEntityID();
    ultrasonido_cont=0;
    rondacion_cont=0;

    data->setData("id2",new BInt(PlayerTransform->getEntityID()));

    //data->serData()
    //// std::cout << "arbol1" << '\n';
    //// std::cout << "creado" << '\n';
    arbol=new Treecontroller(data,0,this);
    //// std::cout << "creadowii" << '\n';

    //// std::cout << "arbol2" << '\n';
    Vrange=30;
    Arange=5;

    playerOnRange=false;
    enfado=0;
    MHandler_SETPTRS();
}

//void CAIEnem::update(){
//    std::list <TriggerRecordStruct*>::iterator it;
//    it=holiiis.begin();
//    TriggerRecordStruct* pTrig=NULL;
//    for(unsigned long i=0; i<holiiis.size();++i)
//    {
//        pTrig=*it;
//        onTriggerStay(pTrig);
//        it++;
//
//    }
//
//
//
//}
gg::EMessageStatus CAIEnem::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CAIEnem::MHandler_SETPTRS(){
    // Inicializando punteros
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    cAgent = static_cast<CAgent*>(Singleton<ObjectManager>::Instance()->getComponent(gg::AGENT, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CAIEnem::MHandler_UPDATE(){
    //// std::cout << "entrando" << '\n';
    float dist =gg::DIST(PlayerTransform->getPosition(),cTransform->getPosition());
    if(dist<Vrange){
        if(!playerSeeing){
            // gg::cout("visto");
            enemyseen();
            arbol->reset();

        }
        if(dist<Arange){
            if(!playerOnRange){
                // gg::cout("rango");
                enemyrange();
            }


        }
        else{
            if(playerOnRange){

                playerOnRange=false;
                // gg::cout("fuera de rango");
            }

        }


    }
    else{
        if(playerSeeing)
        {
            playerSeeing=false;
            arbol->reset();
            gg::cout("dejo de verlo");
        }
    }
    //if(dist<range){
    //}
    //if(dist<range){
    //}
    //enfado++;
    //if(enfado<50){
    //    // std::cout << "iteracion" <<enfado<< '\n';
        //BT->tick();
    //// std::cout << "entrando" << '\n';
    arbol->update();
    //// std::cout << "saliendo" << '\n';
    //}
    return gg::ST_TRUE;

}

void CAIEnem::MHandler_ATURD(){
    // std::cout << "aturd" << '\n';
    ultrasonido=true;
    ultrasonido_cont=0;
    arbol->reset();

}
void CAIEnem::MHandler_NEAR(TriggerRecordStruct* cdata){

}
void CAIEnem::MHandler_SENYUELO(TriggerRecordStruct* cdata){
    senyuelo=true;
    senpos=cdata->vPos;
    arbol->reset();
    // std::cout << "sen in" << '\n';
}
void CAIEnem::MHandler_SENYUELO_END(){
    senyuelo=false;
    // std::cout << "sen out" << '\n';

    arbol->reset();
}
