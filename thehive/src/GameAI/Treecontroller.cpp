#include "Treecontroller.hpp"
#include <BT/RandomSelector.hpp>
#include <BT/RandomSequence.hpp>
//#include <BT/Action.hpp>
#include <BT/Sequence.hpp>
#include <BT/Inverso.hpp>
#include <BT/Selector.hpp>
#include <BT/RandomSelector.hpp>
#include <iostream>

Treecontroller::Treecontroller(){}
//hacer herencia para cada tipo de enemigo ?
Treecontroller::Treecontroller(Blackboard *_data, gg::EEnemyType tipo, CAIEnem* ai){
    yo      = ai;
    data    = _data;

    switch (tipo) {
        case gg::SOLDIER:
            arbolsoldado();
            break;
        case gg::TANK:
            arboltank();
            break;
        case gg::RUSHER:
            arbolrusher();
            break;
        case gg::SWARM:
            arbolswarm();
            break;
        case gg::TRACKER:
            arboltracker();
            break;
    }
}

Action* Treecontroller::addAction(Hojas ac){

    Action* a1= new Action(ac,data,yo);
    m_Children.push_back(a1);
    return a1;


}
Treecontroller::~Treecontroller(){
    for (size_t i = 0; i < m_Children.size(); i++) {
        delete m_Children[i];
    }
    if(BT!=nullptr){
        delete BT;
    }
    if(data!=nullptr){
        delete data;
    }
}

void Treecontroller::reset(){
    for (size_t i = 0; i < m_Children.size(); i++) {
        //// std::cout << "borra" << i<<'\n';
        m_Children[i]->abort();
    }
}
int Treecontroller::taskactual(){
    for (size_t i = 0; i < m_Children.size(); i++) {
        //// std::cout << "borra" << i<<'\n';
        if(m_Children[i]->getStatus()==BH_RUNNING){
            //CAIEnem* AIEnem = static_cast<CAIEnem*>(Manager->getComponent(gg::AIENEM,id));

            return static_cast<Action*>(m_Children[i])->getTask();
        }
    }
    return -1;
}

void Treecontroller::update(){
    BT->tick();
}

void Treecontroller::arboltracker(){
    BT= new BehaviorTree(addAction(GIRAR));
}
void Treecontroller::arbolswarm(){
    BT= new BehaviorTree(addAction(GIRAR));
}

void Treecontroller::arbolrusher(){


    Sequence* sec20= new Sequence();
    sec20->addChild(addAction(ON_RANGE));
    sec20->addChild(addAction(HIT));

    Sequence* sec1= new Sequence();
    sec1->addChild(addAction(RANGO_ULTRASONIDO));
    sec1->addChild(addAction(ATURDIDO));

    Sequence* sec2= new Sequence();
    sec2->addChild(addAction(RANGO_SENYUELO));
    sec2->addChild(addAction(MOVER_SENYUELO));
    sec2->addChild(addAction(RONDAR_SENYUELO));

    Sequence* sec5= new Sequence();
    sec5->addChild(addAction(PRE_DASH_TO_PLAYER));//cargar dash movimiento hacia el jugador
    sec5->addChild(addAction(DASH));//dash
    Sequence* sec4= new Sequence();
    sec4->addChild(addAction(ON_RANGE));
    sec4->addChild(addAction(PRE_DASH_TO_PLAYER));//cargar dash ataque hacia jugador
    sec4->addChild(addAction(DASH));//dash de ataque
    Selector* sel1= new Selector();
    sel1->addChild(sec4);
    sel1->addChild(sec5);
    Sequence* sec3= new Sequence();
    sec3->addChild(addAction(PLAYER_SEEING));
    sec3->addChild(sel1);

    Sequence* sec8= new Sequence();
    sec8->addChild(addAction(GIRAR));//cargar dash
    sec8->addChild(addAction(GIRAR));//dash por la zona
    Sequence* sec9= new Sequence();
    sec9->addChild(addAction(PRE_DASH_TO_LAST_PLAYER));//cargar hacia ultima posicion
    sec9->addChild(addAction(DASH));//dash
    Sequence* sec7= new Sequence();
    sec7->addChild(addAction(IN_LAST_POS_KWON));
    sec7->addChild(sec9);
    Selector* sel3= new Selector();
    sel3->addChild(sec7);
    sel3->addChild(sec8);//no llega
    Selector* sel2= new Selector();
    sel2->addChild(addAction(PLAYER_SEEN));//visto al jugador
    sel2->addChild(addAction(PLAYER_SEEN));//oido al jugador, te trata a la vista y al oidocomo a uno
    Sequence* sec6= new Sequence();
    sec6->addChild(sel2);
    sec6->addChild(sel3);


    Sequence* sec10= new Sequence();//cargar dash random+
    sec10->addChild(addAction(MOVE_AROUND));
    //sec10->addChild(addAction(GIRAR));//cargar dash random
    //sec10->addChild(addAction(GIRAR));//dash random


    Selector* sel4= new Selector();
    sel4->addChild(sec20);
    sel4->addChild(sec1);
    sel4->addChild(sec2);
    sel4->addChild(sec3);
    sel4->addChild(sec6);
    sel4->addChild(sec10);


    m_Children.push_back(sec1);
    m_Children.push_back(sec2);
    m_Children.push_back(sec20);
    m_Children.push_back(sec3);
    m_Children.push_back(sec4);
    m_Children.push_back(sec5);
    m_Children.push_back(sec6);
    m_Children.push_back(sec7);
    m_Children.push_back(sec8);
    m_Children.push_back(sec9);
    m_Children.push_back(sec10);

    m_Children.push_back(sel1);
    m_Children.push_back(sel2);
    m_Children.push_back(sel3);
    m_Children.push_back(sel4);



    BT= new BehaviorTree(sel4);

}

void Treecontroller::arboltank(){


    Sequence* sec1= new Sequence();
    sec1->addChild(addAction(RANGO_ULTRASONIDO));
    sec1->addChild(addAction(ATURDIDO));

    Sequence* sec2= new Sequence();
    sec2->addChild(addAction(RANGO_SENYUELO));
    sec2->addChild(addAction(MOVER_SENYUELO));
    sec2->addChild(addAction(RONDAR_SENYUELO));

    Selector* sel2= new Selector();//random selector?
    sel2->addChild(addAction(EXPANSIVE_WAVE));
    sel2->addChild(addAction(SPIT));
    Sequence* sec6= new Sequence();
    sec6->addChild(addAction(FIVE_SINCELASTHABILITY));
    sec6->addChild(sel2);
    Sequence* sec5= new Sequence();//eing?
    sec5->addChild(addAction(ENEMY_OVER_2_METERS));   // Por encima de 2 metros
    sec5->addChild(addAction(TEN_METROS));     // Por debajo de 10 metros
    sec5->addChild(sec6);
    Sequence* sec4= new Sequence();
    sec4->addChild(addAction(ON_RANGE));
    sec4->addChild(addAction(HIT));
    Selector* sel1= new Selector();
    sel1->addChild(sec4);
    sel1->addChild(sec5);
    sel1->addChild(addAction(MOVE_TO_PLAYER));
    Sequence* sec3= new Sequence();
    sec3->addChild(addAction(PLAYER_SEEING));
    sec3->addChild(sel1);

    Sequence* sec8= new Sequence();
    sec8->addChild(addAction(IN_LAST_POS_KWON));
    sec8->addChild(addAction(MOVE_TO_LAST_POS_KWON));
    Selector* sel4= new Selector();
    sel4->addChild(sec8);
    sel4->addChild(addAction(GIRAR));//patrullar la zona
    Selector* sel3= new Selector();
    sel3->addChild(addAction(PLAYER_SEEN));
    sel3->addChild(addAction(PLAYER_SEEN));
    Sequence* sec7= new Sequence();
    sec7->addChild(sel3);
    sec7->addChild(sel4);



    Selector* sel5= new Selector();
    sel5->addChild(sec1);
    sel5->addChild(sec2);
    sel5->addChild(sec3);
    sel5->addChild(sec7);
    sel5->addChild(addAction(MOVE_AROUND));


    m_Children.push_back(sec1);
    m_Children.push_back(sec2);
    m_Children.push_back(sec3);
    m_Children.push_back(sec4);
    m_Children.push_back(sec5);
    m_Children.push_back(sec6);
    m_Children.push_back(sec7);
    m_Children.push_back(sec8);

    m_Children.push_back(sel1);
    m_Children.push_back(sel2);
    m_Children.push_back(sel3);
    m_Children.push_back(sel4);
    m_Children.push_back(sel5);

    BT= new BehaviorTree(sel5);
}

void Treecontroller::arbolsoldado(){


    Sequence* sec1= new Sequence();
    sec1->addChild(addAction(RANGO_ULTRASONIDO));
    sec1->addChild(addAction(ATURDIDO));

    Sequence* sec2= new Sequence();
    sec2->addChild(addAction(RANGO_SENYUELO));
    sec2->addChild(addAction(MOVER_SENYUELO));
    sec2->addChild(addAction(RONDAR_SENYUELO));



    Sequence* sec9= new Sequence();//bloauqer ruta no esta hecho
    sec9->addChild(addAction(COMER));//no esta en la ruta
    sec9->addChild(addAction(COMER));//calcular ruta a bloquear
    sec9->addChild(addAction(COMER));//mover
    RandomSelector* rsel1=new RandomSelector();
    rsel1->addChild(sec9);
    rsel1->addChild(addAction(PAUSE));
    rsel1->addChild(addAction(RONDAR_PLAYER));
    rsel1->addChild(addAction(MOVEP_UNTILX));
    /////
    Sequence* sec7= new Sequence();
    sec7->addChild(addAction(MOVE_TO_PLAYER));
    //pasado tiempo desde la vez anterior
    sec7->addChild(addAction(HIT));
    Inverso* inv1=new Inverso(addAction(NOT_ATTACKED));
    Inverso* inv2=new Inverso(addAction(X_ALIENS_ATTACKING));
    Selector* sel3= new Selector();
    sel3->addChild(addAction(IAMATACKING));
    sel3->addChild(inv1);
    sel3->addChild(inv2);
    Sequence* sec5= new Sequence();
    sec5->addChild(sel3);
    sec5->addChild(sec7);
    Selector* sel2= new Selector();
    sel2->addChild(sec5);
    sel2->addChild(rsel1);
    //////////////
    Sequence* sec4= new Sequence();
    sec4->addChild(addAction(ON_RANGE));
    //pasado tiempo desde la vez anterior
    sec4->addChild(addAction(HIT));
    Selector* sel1= new Selector();
    sel1->addChild(sec4);
    sel1->addChild(sel2);
    Sequence* sec3= new Sequence();
    sec3->addChild(addAction(PLAYER_SEEING));
    sec3->addChild(sel1);

    Sequence* sec11= new Sequence();
    sec11->addChild(addAction(IN_LAST_POS_KWON));
    sec11->addChild(addAction(MOVE_TO_LAST_POS_KWON));
    Selector* sel6= new Selector();
    sel6->addChild(sec11);
    sel6->addChild(addAction(GIRAR));//patrullar la zona, no llega nunca
    Selector* sel5= new Selector();
    sel5->addChild(addAction(PLAYER_SEEN));//visto al jugador
    sel5->addChild(addAction(PLAYER_SEEN));//oido al jugador, te trata a la vista y al oidocomo a uno
    Sequence* sec10= new Sequence();
    sec10->addChild(sel5);
    sec10->addChild(sel6);

    //rama de los animales muertos
    Sequence* sec12= new Sequence();
    sec12->addChild(addAction(GIRAR));//animal en rango
    sec12->addChild(addAction(GIRAR));//no hay mas de 3 comiendo
    sec12->addChild(addAction(GIRAR));//mover
    sec12->addChild(addAction(GIRAR));//comer
    Selector* sel7= new Selector();
    sel7->addChild(addAction(MOVE_AROUND));
    sel7->addChild(sec12);


    Selector* sel8= new Selector();
    sel8->addChild(sec1);
    sel8->addChild(sec2);
    sel8->addChild(sec3);
    sel8->addChild(sec10);
    sel8->addChild(sel7);

    m_Children.push_back(sec1);
    m_Children.push_back(sec2);
    m_Children.push_back(sec3);
    m_Children.push_back(sec4);
    m_Children.push_back(sec5);
    //m_Children.push_back(sec6);
    m_Children.push_back(sec7);
    //m_Children.push_back(sec8);
    m_Children.push_back(sec9);
    m_Children.push_back(sec10);
    m_Children.push_back(sec11);
    m_Children.push_back(sec12);

    m_Children.push_back(sel1);
    m_Children.push_back(sel2);
    m_Children.push_back(sel3);
    //m_Children.push_back(sel4);
    m_Children.push_back(sel5);
    m_Children.push_back(sel6);
    m_Children.push_back(sel7);
    m_Children.push_back(sel8);
    m_Children.push_back(rsel1);
    m_Children.push_back(inv1);
    m_Children.push_back(inv2);


    BT= new BehaviorTree(sel8);
}
