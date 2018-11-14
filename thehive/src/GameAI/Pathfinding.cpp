#include "Pathfinding.hpp"
#include <iostream>

//  CONNECTION  --
Connection::Connection(uint16_t _From, uint16_t _To, float _Value)
:From(_From), To(_To), Value(_Value)
{}

Connection::Connection(const Connection &orig) {
    From    =   orig.From;
    To      =   orig.To;
    Value   =   orig.Value;
}

//  NODE    --
Node::Node(uint16_t _ID)
:ID(_ID), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED)
{}

Node::Node(const Node &orig){
    std::cout << "Copiando Nodo..." << '\n';

    for(uint8_t i = 0; i < orig.Connections.size(); ++i)
        Connections.push_back(orig.Connections[i]);
    ID              =   orig.ID;
    RealCost        =   orig.RealCost;
    EstimatedCost   =   orig.EstimatedCost;
    Status          =   orig.Status;
}

void Node::AddConnection(const Connection &connection){
    Connections.push_back(connection);
}


//  COMPARATOR
uint16_t Comparator::operator()(const Node &N1, const Node &N2){
    return N1.RealCost < N2.RealCost ? N1.ID : N2.ID;
}

Pathfinding::Pathfinding(){
    {
        //  NODO A
        GRAPH.emplace_back(0);
        Connection AB(0, 1, 1.3f);
        Connection AC(0, 2, 1.1f);
        GRAPH.back().AddConnection(AB);
        GRAPH.back().AddConnection(AC);
        GRAPH.back().Heuristic = 4.2f;
    }

    {
        //  NODO B
        GRAPH.emplace_back(1);
        Connection BD(1, 3, 1.5f);
        Connection BE(1, 4, 1.7f);
        GRAPH.back().AddConnection(BD);
        GRAPH.back().AddConnection(BE);
        GRAPH.back().Heuristic = 3.2f;
    }

    {
        //  NODO C
        GRAPH.emplace_back(2);
        Connection CE(2, 4, 1.5f);
        Connection CF(2, 5, 1.6f);
        GRAPH.back().AddConnection(CE);
        GRAPH.back().AddConnection(CF);
        GRAPH.back().Heuristic = 3.7f;
    }

    {
        //  NODO D
        GRAPH.emplace_back(3);
        GRAPH.back().Heuristic = 2.8f;
    }

    {
        //  NODO E
        GRAPH.emplace_back(4);
        Connection EG(4, 6, 1.4f);
        GRAPH.back().AddConnection(EG);
        GRAPH.back().Heuristic = 1.6f;
    }

    {
        //  NODO F
        GRAPH.emplace_back(5);
        GRAPH.back().Heuristic = 1.4f;
    }

    {
        //  NODO G
        GRAPH.emplace_back(6);
        GRAPH.back().Heuristic = 0.0f;
    }

}

Pathfinding::Pathfinding(const Pathfinding &orig){

}

Pathfinding::~Pathfinding(){

}




void Pathfinding::A_Estrella(){
    //Node CurrentNode    =   GRAPH.back();
    //GRAPH.back().Status = Type::OPEN;
    //OpenList.push(CurrentNode);

    //while(OpenList.size() > 0){
    //    if(OpenList.top().ID == 6) // GOAL
    //        break;

    //    for(Connection c : GRAPH[OpenList.top().ID].Connections){
    //        //if      (GRAPH[c.To].Status == Type::CLOSED)    {
    //        //    if(GRAPH[c.To].RealCost < OpenList.top().RealCost)
    //        //}
    //        //else if (GRAPH[c.To].Status == Type::OPEN)      {

    //        //}
    //        //else    (GRAPH[c.To].Status == Type::UNVISITED) {

    //        //}
    //    }
    //}

}

