#include "Treecontroller.hpp"
#include <BT/RandomSelector.hpp>
#include <BT/RandomSequence.hpp>
//#include <BT/Action.hpp>
#include <BT/Sequence.hpp>
#include <BT/Inverso.hpp>
#include <BT/Selector.hpp>
#include <BT/Parallel.hpp>
#include <BT/UntilFail.hpp>
#include <BT/RandomSelector.hpp>
//#include <iostream>

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
        //// //std::cout << "borra" << i<<'\n';
        m_Children[i]->abort();
    }
}
int Treecontroller::taskactual(){
    for (size_t i = 0; i < m_Children.size(); i++) {
        //// //std::cout << "borra" << i<<'\n';
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
    Sequence* sec6= createSequence();//cargar dash random+
    sec6->addChild(addAction(ON_RANGE));
    sec6->addChild(addAction(KAMIKACE));

    Selector* sel4= createSelector();
    sel4->addChild(addAction(PLAYER_SEEN));
    sel4->addChild(addAction(PLAYER_SEEING));
    Parallel* pal5=createParallel(sel4);
    pal5->addChild(addAction(MOVE_AROUND));//animal en rango
    Inverso* inv3=createInverso(addAction(PLAYER_SEEING));
    Parallel* pal1=createParallel(inv3);
    pal1->addChild(addAction(MOVE_TO_PLAYER));//animal en rango
    Parallel* pal4=createParallel(addAction(PLAYER_SEEING));
    pal4->addChild(addAction(LOOKAROUND));//animal en rango
    Parallel* pal3=createParallel(addAction(PLAYER_SEEING));
    pal3->addChild(addAction(MOVE_TO_LAST_POS_KWON));//animal en rango
    Sequence* sec5= createSequence();
    sec5->addChild(addAction(PLAYER_SEEN));
    sec5->addChild(pal3);
    sec5->addChild(pal4);
    Sequence* sec4= createSequence();
    sec4->addChild(addAction(PLAYER_SEEING));
    sec4->addChild(pal1);
    Sequence* sec3= createSequence();
    sec3->addChild(addAction(RANGO_SENYUELO));
    sec3->addChild(addAction(MOVER_SENYUELO));
    Sequence* sec2= createSequence();
    sec2->addChild(addAction(RANGO_ULTRASONIDO));
    sec2->addChild(addAction(ATURDIDO));
    Selector* sel1= createSelector();//random selector?
    sel1->addChild(sec2);
    sel1->addChild(sec3);
    sel1->addChild(sec4);
    sel1->addChild(sec5);
    sel1->addChild(pal5);
    Sequence* sec1= createSequence();//cargar dash random+
    sec1->addChild(addAction(IAMLEADER));
    sec1->addChild(sel1);

    Selector* sel2= createSelector();//random selector?
    sel2->addChild(sec6);
    sel2->addChild(sec1);
    sel2->addChild(addAction(FOLLOWLEADER));




    BT= new BehaviorTree(sel2);
}

void Treecontroller::arbolrusher(){


    Sequence* sec20= createSequence();
    sec20->addChild(addAction(ON_RANGE));
    sec20->addChild(addAction(HIT));

    Sequence* sec1= createSequence();
    sec1->addChild(addAction(RANGO_ULTRASONIDO));
    sec1->addChild(addAction(ATURDIDO));

    Sequence* sec2= createSequence();
    sec2->addChild(addAction(RANGO_SENYUELO));
    sec2->addChild(addAction(MOVER_SENYUELO));
    sec2->addChild(addAction(RONDAR_SENYUELO));

    Selector* sel66= createSelector();
    sel66->addChild(addAction(ON_RANGE));
    Parallel* pal11=createParallel(sel66);
    pal11->addChild(addAction(DASH));//animal en rango

    //Inverso* inv3=createInverso(addAction(PLAYER_SEEING));
    Selector* sel6= createSelector();
    //sel6->addChild(inv3);
    sel6->addChild(addAction(ON_RANGE));
    Parallel* pal1=createParallel(sel6);
    pal1->addChild(addAction(DASH));//animal en rango

    Sequence* sec5= createSequence();
    sec5->addChild(addAction(PRE_DASH_TO_PLAYER));//cargar dash movimiento hacia el jugador
    sec5->addChild(pal1);//dash
    Sequence* sec4= createSequence();
    sec4->addChild(addAction(ON_RANGE));
    sec4->addChild(addAction(PRE_DASH_TO_PLAYER));//cargar dash ataque hacia jugador
    sec4->addChild(pal11);//dash de ataque//no implementado
    Selector* sel1= createSelector();
    sel1->addChild(sec4);
    sel1->addChild(sec5);
    Sequence* sec3= createSequence();
    sec3->addChild(addAction(PLAYER_SEEING));
    sec3->addChild(sel1);


    Inverso* inv1=createInverso(addAction(PLAYER_SEEN));

    Parallel* pal4=createParallel(addAction(PLAYER_SEEING));
    pal4->addChild(addAction(LOOKAROUND));//animal en rango
    Parallel* pal3=createParallel(addAction(PLAYER_SEEING));
    pal3->addChild(addAction(DASH));//animal en rango
    Sequence* sec6= createSequence();
    sec6->addChild(addAction(PLAYER_SEEN));
    sec6->addChild(addAction(PRE_DASH_TO_LAST_PLAYER));
    sec6->addChild(pal3);
    sec6->addChild(inv1);
    sec6->addChild(pal4);


    Selector* sel5= createSelector();
    sel5->addChild(addAction(PLAYER_SEEN));
    sel5->addChild(addAction(PLAYER_SEEING));
    Parallel* pal5=createParallel(sel5);
    pal5->addChild(addAction(MOVE_AROUND));//animal en rango


    //Sequence* sec10= createSequence();//cargar dash random+
    //sec10->addChild(addAction(MOVE_AROUND));
    //sec10->addChild(addAction(GIRAR));//cargar dash random
    //sec10->addChild(addAction(GIRAR));//dash random


    Selector* sel4= createSelector();
    sel4->addChild(sec20);
    sel4->addChild(sec1);
    sel4->addChild(sec2);
    sel4->addChild(sec3);
    sel4->addChild(sec6);
    sel4->addChild(pal5);




    BT= new BehaviorTree(sel4);

}

void Treecontroller::arboltank(){


    Sequence* sec1= createSequence();
    sec1->addChild(addAction(RANGO_ULTRASONIDO));
    sec1->addChild(addAction(ATURDIDO));

    Sequence* sec2= createSequence();
    sec2->addChild(addAction(RANGO_SENYUELO));
    sec2->addChild(addAction(MOVER_SENYUELO));
    sec2->addChild(addAction(RONDAR_SENYUELO));


    Inverso* inv3=createInverso(addAction(PLAYER_SEEING));
    Parallel* pal1=createParallel(inv3);
    pal1->addChild(addAction(MOVE_TO_PLAYER));//animal en rango

    Selector* sel2= createSelector();//random selector?
    sel2->addChild(addAction(EXPANSIVE_WAVE));
    sel2->addChild(addAction(SPIT));
    Sequence* sec6= createSequence();
    sec6->addChild(addAction(FIVE_SINCELASTHABILITY));
    sec6->addChild(sel2);
    Sequence* sec5= createSequence();//eing?
    sec5->addChild(addAction(ENEMY_OVER_2_METERS));   // Por encima de 2 metros
    sec5->addChild(addAction(TEN_METROS));     // Por debajo de 10 metros
    sec5->addChild(sec6);
    Sequence* sec4= createSequence();
    sec4->addChild(addAction(ON_RANGE));
    sec4->addChild(addAction(HIT));
    Selector* sel1= createSelector();
    sel1->addChild(sec4);
    sel1->addChild(sec5);
    sel1->addChild(pal1);
    //sel1->addChild(addAction(MOVE_TO_PLAYER));//acabar cuando deje de verlo
    Sequence* sec3= createSequence();
    sec3->addChild(addAction(PLAYER_SEEING));
    sec3->addChild(sel1);



    Parallel* pal4=createParallel(addAction(PLAYER_SEEING));
    pal4->addChild(addAction(LOOKAROUND));//animal en rango
    Parallel* pal3=createParallel(addAction(PLAYER_SEEING));
    pal3->addChild(addAction(MOVE_TO_LAST_POS_KWON));//animal en rango
    Sequence* sec8= createSequence();
    sec8->addChild(addAction(PLAYER_SEEN));
    sec8->addChild(pal3);
    sec8->addChild(pal4);



    Selector* sel4= createSelector();
    sel4->addChild(addAction(PLAYER_SEEN));
    sel4->addChild(addAction(PLAYER_SEEING));
    Parallel* pal5=createParallel(sel4);
    pal5->addChild(addAction(MOVE_AROUND));//animal en rango
    Selector* sel5= createSelector();
    sel5->addChild(sec1);
    sel5->addChild(sec2);
    sel5->addChild(sec3);
    sel5->addChild(sec8);
    sel5->addChild(pal5);//



    BT= new BehaviorTree(sel5);
}




void Treecontroller::arbolsoldado(){


    Sequence* sec1= createSequence();
    sec1->addChild(addAction(RANGO_ULTRASONIDO));
    sec1->addChild(addAction(ATURDIDO));

    Sequence* sec2= createSequence();
    sec2->addChild(addAction(RANGO_SENYUELO));
    sec2->addChild(addAction(MOVER_SENYUELO));
    sec2->addChild(addAction(RONDAR_SENYUELO));


    Inverso* inv4=createInverso(addAction(PLAYER_SEEING));
    Parallel* pal2=createParallel(inv4);
    pal2->addChild(addAction(RONDAR_PLAYER));//animal en rango
    RandomSelector* rsel1=createRandomSelector();
    rsel1->addChild(addAction(PAUSE));
    rsel1->addChild(pal2);//poner pal
    rsel1->addChild(addAction(MOVEP_UNTILX));
    Inverso* inv3=createInverso(addAction(PLAYER_SEEING));
    Parallel* pal1=createParallel(inv3);
    pal1->addChild(addAction(MOVE_TO_PLAYER));//animal en rango
    Inverso* inv1=createInverso(addAction(NOT_ATTACKED));
    Inverso* inv2=createInverso(addAction(X_ALIENS_ATTACKING));
    Selector* sel3= createSelector();
    sel3->addChild(addAction(IAMATACKING));
    sel3->addChild(inv1);
    sel3->addChild(inv2);
    Sequence* sec5= createSequence();
    sec5->addChild(sel3);
    sec5->addChild(pal1);
    Selector* sel2= createSelector();
    sel2->addChild(sec5);
    sel2->addChild(rsel1);
    Sequence* sec4= createSequence();
    sec4->addChild(addAction(ON_RANGE));
    sec4->addChild(addAction(HIT));
    Selector* sel1= createSelector();
    sel1->addChild(sec4);
    sel1->addChild(sel2);
    Sequence* sec3= createSequence();
    sec3->addChild(addAction(PLAYER_SEEING));
    sec3->addChild(sel1);



    Parallel* pal4=createParallel(addAction(PLAYER_SEEING));
    pal4->addChild(addAction(LOOKAROUND));//animal en rango
    Parallel* pal3=createParallel(addAction(PLAYER_SEEING));
    pal3->addChild(addAction(MOVE_TO_LAST_POS_KWON));//animal en rango
    Sequence* sec6= createSequence();
    sec6->addChild(addAction(PLAYER_SEEN));
    sec6->addChild(pal3);
    sec6->addChild(pal4);


    Selector* sel4= createSelector();
    sel4->addChild(addAction(PLAYER_SEEN));
    sel4->addChild(addAction(PLAYER_SEEING));
    Parallel* pal5=createParallel(sel4);
    pal5->addChild(addAction(MOVE_AROUND));//animal en rango


    Selector* sel5= createSelector();
    sel5->addChild(sec1);
    sel5->addChild(sec2);
    sel5->addChild(sec3);
    sel5->addChild(sec6);
    sel5->addChild(pal5);



    BT= new BehaviorTree(sel5);
}
Parallel* Treecontroller::createParallel(Behavior* condiciones){

    Inverso* inv=createInverso(condiciones);
    UntilFail* fail=new UntilFail(inv);
    Parallel* pal =new Parallel(RequireOne,RequireOne);
    pal->addChild(fail);

    m_Children.push_back(fail);
    m_Children.push_back(pal);

    return pal;


}
Inverso* Treecontroller::createInverso(Behavior* condiciones){
    Inverso* inv4=new Inverso(condiciones);
    m_Children.push_back(inv4);
    return inv4;
}
Sequence* Treecontroller::createSequence(){

    Sequence* sec1= new Sequence();
    m_Children.push_back(sec1);
    return sec1;

}
Selector* Treecontroller::createSelector(){

    Selector* sec1= new Selector();
    m_Children.push_back(sec1);
    return sec1;

}
RandomSelector* Treecontroller::createRandomSelector(){

    RandomSelector* sec1= new RandomSelector();
    m_Children.push_back(sec1);
    return sec1;

}
