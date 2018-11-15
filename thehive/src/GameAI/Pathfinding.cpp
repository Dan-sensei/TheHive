#include "Pathfinding.hpp"
#include <iostream>

//  CONNECTION  --
Connection::Connection(uint16_t _From, uint16_t _To, float _Value, std::string _Name)
:From(_From), To(_To), Value(_Value), Name(_Name)
{}

Connection::Connection(const Connection &orig) {
    From    =   orig.From;
    To      =   orig.To;
    Value   =   orig.Value;
    Name    =   orig.Name;
}

//  NODE    --
Node::Node()
:ID(UINT16_MAX), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED)
{}
Node::Node(uint16_t _ID)
:ID(_ID), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED)
{}

Node::Node(const Node &orig){
    //std::cout << "Copiando Nodo..." << '\n';

    ID              =   orig.ID;
    Bitconnect      =   orig.Bitconnect;
    RealCost        =   orig.RealCost;
    EstimatedCost   =   orig.EstimatedCost;
    Status          =   orig.Status;
}


//  COMPARATOR
uint16_t Comparator::operator()(const Node &N1, const Node &N2){
    return N1.RealCost < N2.RealCost ? N1.ID : N2.ID;
}

Pathfinding::Pathfinding(){
    {
        //  NODO A
        GRAPH.emplace_back(0);
        Connection AB(0, 1, 1.3f, "AB");
        Connection AC(0, 2, 1.1f, "AC");
        GRAPH.back().Heuristic = 4.2f;
        GConnections[0].push_back(AB);
        GConnections[0].push_back(AC);
    }


    {
        //  NODO B
        GRAPH.emplace_back(1);
        Connection BD(1, 3, 1.5f, "BD");
        Connection BE(1, 4, 1.7f, "BE");
        GRAPH.back().Heuristic = 3.2f;
        GConnections[1].push_back(BD);
        GConnections[1].push_back(BE);
    }

    {
        //  NODO C
        GRAPH.emplace_back(2);
        Connection CE(2, 4, 1.5f, "CE");
        Connection CF(2, 5, 1.6f, "CF");
        GRAPH.back().Heuristic = 3.7f;
        GConnections[2].push_back(CE);
        GConnections[2].push_back(CF);
    }

    {
        //  NODO D
        GRAPH.emplace_back(3);
        GRAPH.back().Heuristic = 2.8f;
    }

    {
        //  NODO E
        GRAPH.emplace_back(4);
        Connection EG(4, 6, 1.4f, "EG");
        GRAPH.back().Heuristic = 1.6f;
        GConnections[2].push_back(EG);
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
    GRAPH[0].Status = Type::OPEN;
    OpenList.push(GRAPH[0]);

    Node CurrentNode;

    while(OpenList.size() > 0){
        CurrentNode    =   OpenList.top();
        OpenList.pop();

        if(CurrentNode.ID == 6) // GOAL
            break;

        std::vector<Connection> Connections = GConnections[CurrentNode.ID];
        for(Connection c : Connections) {

            float costToNode = CurrentNode.RealCost + c.Value;
            if      (GRAPH[c.To].Status == Type::CLOSED)    {

                if(GRAPH[c.To].RealCost <= costToNode)
                    continue;

                GRAPH[c.To].Status = Type::OPEN;
                OpenList.push(GRAPH[c.To]);

            }
            else if (GRAPH[c.To].Status == Type::OPEN)      {
                if(GRAPH[c.To].RealCost <= costToNode)
                    continue;
            }
            else {
                GRAPH[c.To].RealCost = costToNode;
                GRAPH[c.To].Bitconnect = c;
                GRAPH[c.To].EstimatedCost = costToNode + GRAPH[c.To].Heuristic;

                GRAPH[c.To].Status = Type::OPEN;
                OpenList.push(GRAPH[c.To]);
            }
        } //FOR-LOOP end

        GRAPH[CurrentNode.ID].Status = Type::CLOSED;
    }

    if(CurrentNode.ID != 6){
        std::cout << "CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR" << '\n';
    }
    else{
        std::vector<Connection> path;
        while(CurrentNode.ID != 0){
            path.push_back(CurrentNode.Bitconnect);
            //std::cout << CurrentNode.Bitconnect.Name << " - ";
            CurrentNode = GRAPH[CurrentNode.Bitconnect.From];
        }

        std::cout << "CAMINO: " << '\n';

        uint8_t i = path.size();
        while(i--) std::cout << path[i].Name << '-';

        std::cout << '\n';
    }

}

float CalculateHeuristic() {


    return 0;
}