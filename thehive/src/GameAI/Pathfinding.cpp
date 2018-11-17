#include "Pathfinding.hpp"
#include <iostream>
#include <cmath>

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
:ID(UINT16_MAX), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED), X(0.f), Y(0.f)
{}
Node::Node(uint16_t _ID, float _X, float _Y)
:ID(_ID), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED), X(_X), Y(_Y)
{}

Node::Node(const Node &orig){
    //std::cout << "Copiando Nodo..." << '\n';

    ID              =   orig.ID;
    Bitconnect      =   orig.Bitconnect;
    RealCost        =   orig.RealCost;
    EstimatedCost   =   orig.EstimatedCost;
    Status          =   orig.Status;
    X               =   orig.X;
    Y               =   orig.Y;
}


//  COMPARATOR
bool Comparator::operator()(const Node* N1, const Node* N2){
    return N1->RealCost > N2->RealCost;
}

#define GOAL 9
Pathfinding::Pathfinding(){

        //  NODO A         ID   X  Y
        GRAPH.emplace_back(0,    0,  0);
        GRAPH.emplace_back(1,    7,  3);
        GRAPH.emplace_back(2,    3,  7);
        GRAPH.emplace_back(3,   13,  5);
        GRAPH.emplace_back(4,   11,  9);
        GRAPH.emplace_back(5,    6, 13);
        GRAPH.emplace_back(6,   10, 16);
        GRAPH.emplace_back(7,   18,  7);
        GRAPH.emplace_back(8,   17, 14);
        GRAPH.emplace_back(9,   16, 18);

        AddConnection(0, 1);
        AddConnection(0, 2);

        AddConnection(1, 3);

        AddConnection(2, 4);
        AddConnection(2, 5);

        AddConnection(3, 4);
        AddConnection(3, 7);

        AddConnection(4, 6);
        //AddConnection(4, 9);

        AddConnection(5, 4);
        AddConnection(5, 6);

        AddConnection(6, 9);

        AddConnection(7, 8);

        AddConnection(8, 9);

        std::cout << "GRAPH CREATED!" << '\n';

        std::cout << "Connections:" << '\n';
        for(uint16_t i = 0; i < 10; ++i){
            std::cout << "[" << i << "] => ";
            for(uint16_t j = 0; j < GConnections[i].size(); ++j){
                std::cout << GConnections[i][j].Name << " ";
            }
            std::cout << '\n';
        }
}

Pathfinding::Pathfinding(const Pathfinding &orig){

}

Pathfinding::~Pathfinding(){

}


void Pathfinding::AddConnection(uint16_t From, uint16_t To){
    float IncX = GRAPH[To].X - GRAPH[From].X;
    float IncY = GRAPH[To].Y - GRAPH[From].Y;
    float Value = sqrt(IncX*IncX + IncY*IncY);
    std::string Name = std::to_string(From) + std::to_string(To);
    Connection newC(From, To, Value, Name);
    GConnections[From].push_back(newC);
}



void Pathfinding::A_Estrella(){

    GRAPH[0].Status = Type::OPEN;
    OpenList.push(&GRAPH[0]);

    Node* CurrentNode;

    while(OpenList.size() > 0){
        CurrentNode    =   OpenList.top();
        OpenList.pop();

        if(CurrentNode->ID == GOAL) // GOAL
            break;

        std::vector<Connection> Connections = GConnections[CurrentNode->ID];
        for(Connection c : Connections) {

            float costToNode = CurrentNode->RealCost + c.Value;
            if (GRAPH[c.To].Status == Type::CLOSED) {

                if(GRAPH[c.To].RealCost <= costToNode)
                    continue;

                GRAPH[c.To].Status = Type::OPEN;
                OpenList.push(&GRAPH[c.To]);

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
                OpenList.push(&GRAPH[c.To]);
            }
        } //FOR-LOOP end

        CurrentNode->Status = Type::CLOSED;
    }

    if(CurrentNode->ID != GOAL){
        std::cout << "CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR" << '\n';
    }
    else{
        std::vector<Connection> path;
        while(CurrentNode->ID != 0){
            path.push_back(CurrentNode->Bitconnect);
            //std::cout << CurrentNode.Bitconnect.Name << " - ";
            CurrentNode = &GRAPH[CurrentNode->Bitconnect.From];
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