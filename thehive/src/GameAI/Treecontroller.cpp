#include "Treecontroller.hpp"
#include <BT/RandomSelector.hpp>
#include <BT/RandomSequence.hpp>
#include <BT/Action.hpp>
#include <BT/Sequence.hpp>
#include <BT/Selector.hpp>
#include <iostream>


    /* data */
    //void Treecontroller::iniciar (Blackboard* _data){
    //    Treecontroller (Blackboard* _data);

    //}
    Treecontroller::Treecontroller (){

    }

    Treecontroller::Treecontroller (Blackboard* _data){
        data=_data;
        arbolsoldado();

    }
    Treecontroller::~Treecontroller (){
        for (size_t i = 0; i < m_Children.size(); i++) {
            //std::cout << "entra hijo" << '\n';
            //std::cout << "borra" << i<<'\n';
            delete m_Children[i];
        }
        //std::cout << "llega" << '\n';
        if(BT!=nullptr){
            //std::cout << "entra BT" << '\n';
            delete BT;
        }
        if(data!=nullptr){
            //std::cout << "entra data" << '\n';
            delete data;
        }
        //std::cout << "sale" << '\n';

    }
    void Treecontroller::reset(){
        for (size_t i = 0; i < m_Children.size(); i++) {
            //std::cout << "borra" << i<<'\n';
            m_Children[i]->abort();
        }
    }
    void Treecontroller::update(){
        //std::cout << "update1" << '\n';
        BT->tick();
        //std::cout << "update2" << '\n';
    }
    void Treecontroller::arbolsoldado(){

        Action* a1= new Action(TEN_METROS,data);//10 metros del jugador?
        Action* a2= new Action(THREE_ATACK,data);//hay tres atacando?
        Action* a3= new Action(ON_RANGE,data);//estoy a rango?
        Action* a4= new Action(IN_PLACE,data);//no estoy en el lugar?
        Action* a5= new Action(PLAYER_SEEN,data);//he visto al jugador?
        Action* a6= new Action(PLAYER_SEEING,data);//estoy viendo al jugador?
        //acciones
        Action* a7= new Action(MOVE_AROUND,data);//rondar al jugador
        Action* a8= new Action(BLOCK,data);//bloquear el camino
        Action* a9= new Action(MOVE_TO_PLAYER,data);//moverse hacia el jugador
        Action* a10= new Action(HIT,data);//golpear
        Action* a11= new Action(MOVE_TO_LAST_POS_KWON,data);//mover ultima pos
        Action* a12= new Action(JUST_MOVE,data);//mover por el mapa


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
        sel5->addChild(sec4);
        sel5->addChild(sec6);
        sel5->addChild(a12);



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
    }
