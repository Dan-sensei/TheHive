#include "Treecontroller.hpp"
#include <BT/RandomSelector.hpp>
#include <BT/RandomSequence.hpp>
#include <BT/Action.hpp>
#include <BT/Sequence.hpp>
#include <BT/Inverso.hpp>
#include <BT/Selector.hpp>
#include <BT/RandomSelector.hpp>
#include <iostream>

Treecontroller::Treecontroller(){}

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
        case gg::TRACKER:
            arboltracker();
            break;
    }
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
    Action* a1= new Action(TEN_METROS,data,yo);//rango ultrasonido
    Action* a2= new Action(TEN_METROS,data,yo);//aturdido
    Action* a3= new Action(TEN_METROS,data,yo);//rango señuelo
    Action* a4= new Action(TEN_METROS,data,yo);//escupir señuelo
    Action* a5= new Action(TEN_METROS,data,yo);//estoy viendo al jugador
    Action* a6= new Action(TEN_METROS,data,yo);//esta a rango
    Action* a7= new Action(TEN_METROS,data,yo);//no estoy en una zona peligrosa
    Action* a8= new Action(TEN_METROS,data,yo);//escupir
    Action* a9= new Action(TEN_METROS,data,yo);//jugador me esta disparando
    Action* a10= new Action(TEN_METROS,data,yo);//hacerse invisible
    Action* a11= new Action(TEN_METROS,data,yo);//deshacerse de la invisibilidad
    Action* a12= new Action(TEN_METROS,data,yo);//buscar zona no peligrosa cercana
    Action* a13= new Action(TEN_METROS,data,yo);//esta en el mismo edificio en el que estoy ya
    Action* a14= new Action(TEN_METROS,data,yo);//moverse a zona no peligrosa mas cercana
    Action* a15= new Action(TEN_METROS,data,yo);//saltar a la zona no peligrosa mas cercana
    Action* a16= new Action(TEN_METROS,data,yo);//estoy escuchando al jugador
    Action* a17= new Action(TEN_METROS,data,yo);//he visto al jugaodr
    Action* a18= new Action(TEN_METROS,data,yo);//no estoy en la zona
    Action* a19= new Action(TEN_METROS,data,yo);//moverse); a la zona
    Action* a20= new Action(TEN_METROS,data,yo);//patrullar los tejador
    Action* a21= new Action(TEN_METROS,data,yo);//moverse por el mapa


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
    m_Children.push_back(a13);
    m_Children.push_back(a14);
    m_Children.push_back(a15);
    m_Children.push_back(a16);
    m_Children.push_back(a17);
    m_Children.push_back(a18);
    m_Children.push_back(a19);
    m_Children.push_back(a20);
    m_Children.push_back(a21);
}

void Treecontroller::arbolrusher(){
    Action* a1= new Action(TEN_METROS,data,yo);        //rango ultrasonido
    Action* a2= new Action(TEN_METROS,data,yo);        //ATURDIDO
    Action* a3= new Action(TEN_METROS,data,yo);        //rango señuelo
    Action* a4= new Action(TEN_METROS,data,yo);        //mover
    Action* a5= new Action(TEN_METROS,data,yo);        //rondar
    Action* a6= new Action(TEN_METROS,data,yo);        //estoy viendo al jugador
    Action* a7= new Action(TEN_METROS,data,yo);        //esta a rango
    Action* a8= new Action(TEN_METROS,data,yo);        //cargar
    Action* a9= new Action(TEN_METROS,data,yo);        //dash
    Action* a10= new Action(TEN_METROS,data,yo);       //cargar dash
    Action* a11= new Action(TEN_METROS,data,yo);       //dash hacia el jugador
    Action* a12= new Action(TEN_METROS,data,yo);       //estoy escuchando al jugador
    Action* a13= new Action(TEN_METROS,data,yo);       //he visto al jugador
    Action* a14= new Action(TEN_METROS,data,yo);       //no estoy en la zona
    Action* a15= new Action(TEN_METROS,data,yo);       //cargar dash
    Action* a16= new Action(TEN_METROS,data,yo);       //dash hacia la zona
    Action* a17= new Action(TEN_METROS,data,yo);       //cargar dash
    Action* a18= new Action(TEN_METROS,data,yo);       //dash por la zona
    Action* a19= new Action(TEN_METROS,data,yo);       //cargar dash
    Action* a20= new Action(TEN_METROS,data,yo);       //dash random

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
    m_Children.push_back(a13);
    m_Children.push_back(a14);
    m_Children.push_back(a15);
    m_Children.push_back(a16);
    m_Children.push_back(a17);
    m_Children.push_back(a18);
    m_Children.push_back(a19);
    m_Children.push_back(a20);

    Sequence* sec1= new Sequence();
    sec1->addChild(a1);
    sec1->addChild(a2);

    Sequence* sec2= new Sequence();
    sec2->addChild(a3);
    sec2->addChild(a4);
    sec2->addChild(a5);

    Sequence* sec5= new Sequence();
    sec5->addChild(a10);
    sec5->addChild(a11);
    Sequence* sec4= new Sequence();
    sec4->addChild(a7);
    sec4->addChild(a8);
    sec4->addChild(a9);
    Selector* sel1= new Selector();
    sel1->addChild(sec4);
    sel1->addChild(sec5);
    Sequence* sec3= new Sequence();
    sec3->addChild(a6);
    sec3->addChild(sel1);

    Sequence* sec8= new Sequence();
    sec8->addChild(a17);
    sec8->addChild(a18);
    Sequence* sec9= new Sequence();
    sec9->addChild(a15);
    sec9->addChild(a16);
    Sequence* sec7= new Sequence();
    sec7->addChild(a14);
    sec7->addChild(sec9);
    Selector* sel3= new Selector();
    sel3->addChild(sec7);
    sel3->addChild(sec8);
    Selector* sel2= new Selector();
    sel2->addChild(a12);
    sel2->addChild(a13);
    Sequence* sec6= new Sequence();
    sec6->addChild(sel2);
    sec6->addChild(sel3);


    Sequence* sec10= new Sequence();
    sec10->addChild(a19);
    sec10->addChild(a20);


    Selector* sel4= new Selector();
    sel4->addChild(sec1);
    sel4->addChild(sec2);
    sel4->addChild(sec3);
    sel4->addChild(sec6);
    sel4->addChild(sec10);


    m_Children.push_back(sec1);
    m_Children.push_back(sec2);
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
    Action* a1= new Action(RANGO_ULTRASONIDO,data,yo);//rango ultrasonido
    Action* a2= new Action(ATURDIDO,data,yo);//aturdido

    Action* a3= new Action(RANGO_SENYUELO,data,yo);//rango señuelo
    Action* a4= new Action(MOVER_SENYUELO,data,yo);//mover
    Action* a5= new Action(RONDAR_SENYUELO,data,yo);//rondar

    Action* a6= new Action(PLAYER_SEEING,data,yo);//estoy viendo al jugador

    Action* a7= new Action(ON_RANGE,data,yo);//esta el jugado a menos d eun metro
    Action* a8= new Action(HIT,data,yo);//golpar

    Action* a9= new Action(TEN_METROS,data,yo);//esta entre 2-10 metros
    Action* a9_2= new Action(ENEMY_OVER_2_METERS,data,yo);//esta entre 2-10 metros

    Action* a10= new Action(FIVE_SINCELASTHABILITY,data,yo);//ha pasado tiempo desde la vez anterior
    Action* a11= new Action(EXPANSIVE_WAVE,data,yo);//onda expansiva
    Action* a12= new Action(SPIT,data,yo);//escupir

    Action* a13= new Action(MOVE_TO_PLAYER,data,yo);//mover hacia jugdor

    // <NO IMPLEMENTADO>
    Action* a14= new Action(PLAYER_SEEN,data,yo);//estoy escuchando al jugaodr
    Action* a15= new Action(PLAYER_SEEN,data,yo);//he visto al jugaodr

    Action* a16= new Action(IN_LAST_POS_KWON,data,yo);//no estoy en la zona
    Action* a17= new Action(MOVE_TO_LAST_POS_KWON,data,yo);//moverse hacia la zona

    Action* a18= new Action(GIRAR,data,yo);//patrullar la zona
    // </NO IMPLEMENTADO>

    Action* a19= new Action(ANDAR_RAND,data,yo);//andar random

    m_Children.push_back(a1);
    m_Children.push_back(a2);
    m_Children.push_back(a3);
    m_Children.push_back(a4);
    m_Children.push_back(a5);
    m_Children.push_back(a6);
    m_Children.push_back(a7);
    m_Children.push_back(a8);
    m_Children.push_back(a9);
    m_Children.push_back(a9_2);
    m_Children.push_back(a10);
    m_Children.push_back(a11);
    m_Children.push_back(a12);
    m_Children.push_back(a13);
    m_Children.push_back(a14);
    m_Children.push_back(a15);
    m_Children.push_back(a16);
    m_Children.push_back(a17);
    m_Children.push_back(a18);
    m_Children.push_back(a19);



    Sequence* sec1= new Sequence();
    sec1->addChild(a1);
    sec1->addChild(a2);

    Sequence* sec2= new Sequence();
    sec2->addChild(a3);
    sec2->addChild(a4);
    sec2->addChild(a5);

    Sequence* sec4= new Sequence();
    sec4->addChild(a7);
    sec4->addChild(a8);

    Selector* sel2= new Selector();
    sel2->addChild(a11);
    sel2->addChild(a12);

    Sequence* sec6= new Sequence();
    sec6->addChild(a10);
    sec6->addChild(sel2);

    Sequence* sec5= new Sequence();
    sec5->addChild(a9_2);   // Por encima de 2 metros
    sec5->addChild(a9);     // Por debajo de 10 metros
    sec5->addChild(sec6);

    Selector* sel1= new Selector();
    sel1->addChild(sec4);
    sel1->addChild(sec5);
    sel1->addChild(a13);

    Sequence* sec3= new Sequence();
    sec3->addChild(a6);
    sec3->addChild(sel1);

    Sequence* sec8= new Sequence();
    sec8->addChild(a16);
    sec8->addChild(a17);
    Selector* sel4= new Selector();
    sel4->addChild(sec8);
    sel4->addChild(a18);
    Selector* sel3= new Selector();
    sel3->addChild(a14);
    sel3->addChild(a15);
    Sequence* sec7= new Sequence();
    sec7->addChild(sel3);
    sec7->addChild(sel4);



    Selector* sel5= new Selector();
    sel5->addChild(sec1);
    sel5->addChild(sec2);
    sel5->addChild(sec3);
    sel5->addChild(sec7);
    sel5->addChild(a19);


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
    //Inverso
    //RandomSelector
    Action* a1= new Action(RANGO_ULTRASONIDO,data,yo);//rango ultrasonido
    Action* a2= new Action(ATURDIDO,data,yo);//aturdido


    Action* a3= new Action(RANGO_SENYUELO,data,yo);//rango señuelo
    Action* a4= new Action(MOVER_SENYUELO,data,yo);//mover
    Action* a5= new Action(RONDAR_SENYUELO,data,yo);//rondar


    Action* a6= new Action(PLAYER_SEEING,data,yo);//estoy viendo al jugador
    Action* a7= new Action(ON_RANGE,data,yo);//esta a rango
    Action* a8= new Action(HIT,data,yo);//golpear

    Action* a9= new Action(NOT_ATTACKED,data,yo);//el jugador me ha atacado
    Action* a10= new Action(ALLY_DEAD,data,yo);//ha muerto aliado
    Action* a11= new Action(MORE_RAGE,data,yo);//aumentar enfado
    Action* a12= new Action(X_ALIENS_ATTACKING,data,yo);//hay x aliens atacando

    //Action* a13= new Action(X_ALIENS_ATTACKING,data,yo);//hay x aliens atacando no esta ahora
    Action* a13= new Action(MOVEP_UNTILX,data,yo);//hay x aliens atacando no esta ahora

    //Action* a14= new Action(X_METRES_PLAYER,data,yo);// esta a x metros o menos del jugador no est ahora
    Action* a15= new Action(RONDAR_PLAYER,data,yo);//rondar jugador

    Action* a16= new Action(COMER,data,yo);//no esta en la ruta
    Action* a17= new Action(COMER,data,yo);//calcular ruta a bloquear
    Action* a18= new Action(COMER,data,yo);//mover

    Action* a19= new Action(PAUSE,data,yo);//esperar

    Action* a20= new Action(MOVE_TO_PLAYER,data,yo);//moverse en direccion al jugador

    // <NO IMPLEMENTADO>
    Action* a21= new Action(PLAYER_SEEN,data,yo);//estoy escuhando al jugador
    Action* a22= new Action(PLAYER_SEEN,data,yo);//he visto al jugador
    Action* a23= new Action(IN_LAST_POS_KWON,data,yo);//no estoy en la zona
    Action* a24= new Action(MOVE_TO_LAST_POS_KWON,data,yo);//moverse a la zona
    Action* a25= new Action(GIRAR,data,yo);//patrullar la zona

    Action* a26= new Action(MOVE_AROUND,data,yo);//andar random
    Action* a27= new Action(GIRAR,data,yo);//animal en rango
    Action* a28= new Action(GIRAR,data,yo);//no hay mas de 3 comiendo
    Action* a29= new Action(GIRAR,data,yo);//mover
    Action* a30= new Action(GIRAR,data,yo);//comer

    Action* a31= new Action(IAMATACKING,data,yo);//Estoy atacando
    // </NO IMPLEMENTADO>

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
    m_Children.push_back(a13);
    m_Children.push_back(a15);
    m_Children.push_back(a16);
    m_Children.push_back(a17);
    m_Children.push_back(a18);
    m_Children.push_back(a19);
    m_Children.push_back(a20);
    m_Children.push_back(a21);
    m_Children.push_back(a22);
    m_Children.push_back(a23);
    m_Children.push_back(a24);
    m_Children.push_back(a25);
    m_Children.push_back(a26);
    m_Children.push_back(a27);
    m_Children.push_back(a28);
    m_Children.push_back(a29);
    m_Children.push_back(a30);
    m_Children.push_back(a31);

    Sequence* sec1= new Sequence();
    sec1->addChild(a1);
    sec1->addChild(a2);

    Sequence* sec2= new Sequence();
    sec2->addChild(a3);
    sec2->addChild(a4);
    sec2->addChild(a5);


    Sequence* sec9= new Sequence();
    sec9->addChild(a16);
    sec9->addChild(a17);
    sec9->addChild(a18);
    RandomSelector* rsel1=new RandomSelector();
    rsel1->addChild(sec9);
    rsel1->addChild(a19);
    rsel1->addChild(a15);
    rsel1->addChild(a13);

    Sequence* sec7= new Sequence();
    sec7->addChild(a20);
    sec7->addChild(a8);
    Inverso* inv1=new Inverso(a9);
    Inverso* inv2=new Inverso(a12);
    Selector* sel3= new Selector();
    sel3->addChild(a31);
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
    sec4->addChild(a7);
    sec4->addChild(a8);
    Selector* sel1= new Selector();
    sel1->addChild(sec4);
    sel1->addChild(sel2);
    Sequence* sec3= new Sequence();
    sec3->addChild(a6);
    sec3->addChild(sel1);

    Sequence* sec11= new Sequence();
    sec11->addChild(a23);
    sec11->addChild(a24);
    Selector* sel6= new Selector();//5
    sel6->addChild(sec11);
    sel6->addChild(a25);
    Selector* sel5= new Selector();//5
    sel5->addChild(a21);
    sel5->addChild(a22);
    Sequence* sec10= new Sequence();
    sec10->addChild(sel5);
    sec10->addChild(sel6);

    Sequence* sec12= new Sequence();
    sec12->addChild(a27);
    sec12->addChild(a28);
    sec12->addChild(a29);
    sec12->addChild(a30);
    Selector* sel7= new Selector();//5
    sel7->addChild(a26);
    sel7->addChild(sec12);


    Selector* sel8= new Selector();//5
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
