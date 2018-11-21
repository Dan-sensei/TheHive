#include "CAIEnem.hpp"
#include "ComponentArch/Components/CAIEnem.hpp"

#include <ComponentArch/InitStructs.hpp>
#include <GameEngine/GameEngine.hpp>            // [OPCIONAL] Si necesitas acceder a algún método de GameEngine
#include <ComponentArch/ObjectManager.hpp>      // [OPCIONAL] Si necesitas acceder a algún método de ObjectManager
#include <Singleton.hpp>
#include <list>
#include "ComponentArch/Message.hpp"

#include <BT/RandomSelector.hpp>
#include <BT/RandomSequence.hpp>
#include <BT/Action.hpp>


//std::list  <TriggerRecordStruct*>  hola;




//CAIEnem::CAIEnem(unsigned long _dwTriggerFlags,gg::Vector3f _vPos){
//    nCAIEnemID=id2;
//    id2++;
//    dwTriggerFlags=_dwTriggerFlags;
//    nDeltaTime=0;
//    vPos=_vPos;
//}


CAIEnem::CAIEnem()
:cTransform(nullptr),cAgent(nullptr)
{

}

CAIEnem::~CAIEnem() {

}
void CAIEnem::enemyseen(TriggerRecordStruct* cdata){
//
playerPos=cdata->vPos;
playerSeen=true;
playerOnRange=true;
//
}

void CAIEnem::initComponent() {
    //  Si necesitas punteros a otras funciones es importante suscribir esta componente al mensaje M_SETPTRS
    //  Este mensaje se llamará para recalular los punteros cuando se borre una componente de un objeto
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::AIENEM, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::AIENEM, gg::M_SETPTRS);


}

void CAIEnem::initializeComponentData(const void* data){
    if(data){
        InitCAIEnem* cdata=(InitCAIEnem*)data;
            type=cdata->type;
            agresividad=cdata->agresividad;
            playerPos=cdata->playerPos;
            playerSeen=cdata->playerSeen;
/*
            Action* andar_r= new Action(ANDAR_RAND);
            Action* rango= new Action(RANGO);
            Action* giro= new Action(GIRAR);
            Action* move_to= new Action(MOVER);
            Action* com= new Action(COMER);

            RandomSequence* sec1= new RandomSequence();
            sec1->addChild(rango);
            sec1->addChild(giro);

            RandomSequence*  sec2= new RandomSequence();
            sec2->addChild(sec1);
            sec2->addChild(move_to);
            sec2->addChild(com);

            RandomSelector* selec1=  new RandomSelector();
            selec1->addChild(andar_r);
            selec1->addChild(sec2);

            BT=BehaviorTree(selec1);

*/


            //des/activar eventos sonoros


            playerOnRange=false;
            enfado=0;
            //vPos=cTransform->getPosition;
        //CAIEnem(data->dwTriggerFlags,gg::Vector3f _vPos(cTransform->X,cTransform->Y,cTransform->Z));
        // Si le pasamos cosas, convertimos el void* a la estructura inicializadora para acceder a los elementos
    }
    engine = Singleton<GameEngine>::Instance();

    //  Inicializar punteros a otras compnentes
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
    // UPDATE
    //setposition
    //CAIEnem(cTransform->getPosition);
    //if(enfado==0){
    //    enfado ++;
    //    BT.tick();
    //    BT.tick();

    //}
    //std::cout << "updatetrig" << '\n';

    return gg::ST_TRUE;

}
