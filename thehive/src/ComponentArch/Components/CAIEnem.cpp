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
#include <BT/Sequence.hpp>
#include <BT/Selector.hpp>


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
    for (size_t i = 0; i < m_Children.size(); i++) {
        //std::cout << "borra" << i<<'\n';
        delete m_Children[i];
    }
    //std::cout << "llega" << '\n';
    //delete BT;
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

            m_Children.push_back(andar_r);
            m_Children.push_back(rango);
            m_Children.push_back(giro);
            m_Children.push_back(move_to);
            m_Children.push_back(com);

            RandomSequence* sec1= new RandomSequence();
            sec1->addChild(rango);
            sec1->addChild(giro);
            m_Children.push_back(sec1);

            RandomSequence*  sec2= new RandomSequence();
            sec2->addChild(sec1);
            sec2->addChild(move_to);
            sec2->addChild(com);
            m_Children.push_back(sec2);


            RandomSelector* selec1=  new RandomSelector();
            selec1->addChild(andar_r);
            selec1->addChild(sec2);
            m_Children.push_back(selec1);
*/

//condiciones
/*
Action* a1= new Action(10_METROS);//10 metros del jugador?
Action* a2= new Action(3_ATACK);//hay tres atacando?
Action* a3= new Action(ON_RANGE);//estoy a rango?
Action* a4= new Action(IN_PLACE);//no estoy en el lugar?
Action* a5= new Action(PLAYER_SEEN);//he visto al jugador?
Action* a6= new Action(PLAYER_SEEING);//estoy viendo al jugador?
//acciones
Action* a7= new Action(MOVE_AROUND);//rondar al jugador
Action* a8= new Action(BLOCK);//bloquear el camino
Action* a9= new Action(MOVE_TO_PLAYER);//moverse hacia el jugador
Action* a10= new Action(HIT);//golpear
Action* a11= new Action(MOVE_TO_LAST_POS_KWON);//mover ultima pos
Action* a12= new Action(JUST_MOVE);//mover por el mapa


m_Children.push_back(a1);
m_Children.push_back(a2);
m_Children.push_back(a3);
m_Children.push_back(a4);
m_Children.push_back(a5);
m_Children.push_back(a6);
m_Children.push_back(a7);
m_Children.push_back(a8);
m_Children.push_back(a9);
m_Children.push_back(a10);
m_Children.push_back(a11);
m_Children.push_back(a12);


Sequence* sec1= new Sequence();//6
sec1->addChild(a1);
sec1->addChild(a7);
Selector* sel1= new Selector();//5
sel1->addChild(sec1);
sel1->addChild(a8);
Sequence* sec2= new Sequence();//6
sec2->addChild(a2);
sec2->addChild(sel1);
Selector* sel2= new Selector();//5
sel2->addChild(sec2);
sel2->addChild(a9);
Sequence* sec3= new Sequence();//6
sec3->addChild(a3);
sec3->addChild(a10);
Selector* sel3= new Selector();//5
sel3->addChild(sec3);
sel3->addChild(sel2);
Sequence* sec4= new Sequence();//6
sec4->addChild(a6);
sec4->addChild(sel3);


Sequence* sec5= new Sequence();//6
sec5->addChild(a4);
sec5->addChild(a11);
Selector* sel4= new Selector();//5
sel4->addChild(sec5);
sel4->addChild(a12);
Sequence* sec6= new Sequence();//6
sec6->addChild(a5);
sec6->addChild(sel4);


Selector* sel5= new Selector();//5
sec5->addChild(sec4);
sec5->addChild(sec6);
sec5->addChild(a12);





m_Children.push_back(sec1);
m_Children.push_back(sec2);
m_Children.push_back(sec3);
m_Children.push_back(sec4);
m_Children.push_back(sec5);
m_Children.push_back(sec6);

m_Children.push_back(sel1);
m_Children.push_back(sel2);
m_Children.push_back(sel3);
m_Children.push_back(sel4);
m_Children.push_back(sel5);



            BT= new BehaviorTree(sel5);
            */

//BT->tick();


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
    if(enfado==0){
        enfado ++;
        //BT.tick();
        //BT.tick();
        //BT->tick();
        //BT->tick();

    }
    //std::cout << "updatetrig" << '\n';

    return gg::ST_TRUE;

}
