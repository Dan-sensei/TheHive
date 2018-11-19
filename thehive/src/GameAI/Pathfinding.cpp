#include "Pathfinding.hpp"
#include <iostream>
#include "MeshImporter.hpp"
#include "Singleton.hpp"
#include <cmath>
#include <GameEngine/GameEngine.hpp>


//  COMPARATOR
bool Comparator::operator()(const Node* N1, const Node* N2){
    return N1->EstimatedCost > N2->EstimatedCost;
}

Pathfinding::Pathfinding(){

        //  NODO A         ID   X  Y
        //GRAPH.emplace_back(0,    0,  0);
        //GRAPH.emplace_back(1,    7,  3);
        //GRAPH.emplace_back(2,    3,  7);
        //GRAPH.emplace_back(3,   13,  5);
        //GRAPH.emplace_back(4,   11,  9);
        //GRAPH.emplace_back(5,    6, 13);
        //GRAPH.emplace_back(6,   10, 16);
        //GRAPH.emplace_back(7,   18,  7);
        //GRAPH.emplace_back(8,   17, 14);
        //GRAPH.emplace_back(9,   16, 18);
        //GRAPH.emplace_back(10,  20, 02);
        //GRAPH.emplace_back(11,  30, 02);


        //AddConnection(0, 1);
        //AddConnection(0, 2);

        //AddConnection(1, 3);

        //AddConnection(2, 4);
        //AddConnection(2, 5);

        //AddConnection(3, 4);
        //AddConnection(3, 7);

        //AddConnection(4, 6);
        //AddConnection(4, 9);

        //AddConnection(5, 4);
        //AddConnection(5, 6);

        //AddConnection(6, 9);

        //AddConnection(7, 8);

        //AddConnection(8, 9);

        //AddConnection(7, 10);
        //AddConnection(10, 9);
        //AddConnection(10, 11);

        bool loaded = Singleton<MeshImporter>::Instance()->importNavmesh("assets/NavMeshes/Test.obj", GRAPH, GConnections);
        for(uint16_t i = 0; i < GConnections.size(); ++i){
            for(uint16_t j = 0; j < GConnections[i].size(); ++j){
                if(GConnections[i][j].Value == 0)
                    GConnections[i][j].Value = gg::DIST(GRAPH[GConnections[i][j].From].Position, GRAPH[GConnections[i][j].To].Position);
            }
        }

        std::cout << "GRAPH CREATED!" << '\n';

        std::cout << " ->" << GRAPH.size() << " Nodes created!" << '\n';
        for(uint8_t i = 0; i < GRAPH.size(); ++i){
            std::cout << "  -- " << i << " " << GRAPH[i] << '\n';
        }

        std::cout << "Connections:" << '\n';
        for(uint16_t i = 0; i < GConnections.size(); ++i){
            std::cout << "[" << i << "] => ";
            for(uint16_t j = 0; j < GConnections[i].size(); ++j){
                std::cout << GConnections[i][j].Name << " = " << GConnections[i][j].Value << " | ";
            }
            std::cout << '\n';
        }
}

Pathfinding::~Pathfinding(){

}


void Pathfinding::AddConnection(uint16_t From, uint16_t To){
    //float IncX = GRAPH[To].X - GRAPH[From].X;
    //float IncY = GRAPH[To].Y - GRAPH[From].Y;
    //float Value = sqrt(IncX*IncX + IncY*IncY);
    //std::string Name = std::to_string(From) + std::to_string(To);
    //Connection newC(From, To, Value, Name);
    //GConnections[From].push_back(newC);
}

void Pathfinding::resetGraph(){
    uint16_t i = GRAPH.size();
    while(i--){
        GRAPH[i].Status = Type::UNVISITED;
        GRAPH[i].RealCost = 0;
        GRAPH[i].EstimatedCost = 0;
        GRAPH[i].Bitconnect = Connection();
    }
}

void Pathfinding::A_Estrella(uint16_t START, uint16_t GOAL, std::stack<Waypoint> &Output){

    resetGraph();
    OpenList = std::priority_queue<Node*, std::vector<Node*>, Comparator>();

    {
        uint16_t c = 0;
        for(uint16_t i = 0; i < GRAPH.size(); ++i)
            if(GRAPH[i].Status == Type::UNVISITED) ++c;

        std::cout << "GRAPH UNVISITED: " << c << '\n';
        std::cout << "       OPENLIST: " << OpenList.size() << '\n';
    }

    GRAPH[START].Status = Type::OPEN;
    OpenList.push(&GRAPH[START]);

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
        while(CurrentNode->ID != START){
            path.push_back(CurrentNode->Bitconnect);
            //std::cout << CurrentNode.Bitconnect.Name << " - ";
            //Waypoint wp(GRAPH[CurrentNode->Bitconnect.To].Position, CurrentNode->ID);
            //Output.push(wp);
            CurrentNode = &GRAPH[CurrentNode->Bitconnect.From];
        }

        std::cout << "CAMINO: " << '\n';

        uint8_t i = path.size();
        while(i--) std::cout << path[i].Name << '-';

        std::cout << '\n';
    }

    printStats();
    std::cout << "-----------------------------------------------" << '\n';
}

void Pathfinding::A_Estrella2(uint16_t START, uint16_t GOAL, std::stack<Waypoint> &Output){

    resetGraph();
    OpenList = std::priority_queue<Node*, std::vector<Node*>, Comparator>();

    {
        uint16_t c = 0;
        for(uint16_t i = 0; i < GRAPH.size(); ++i)
            if(GRAPH[i].Status == Type::UNVISITED) ++c;

        std::cout << "GRAPH UNVISITED: " << c << '\n';
        std::cout << "       OPENLIST: " << OpenList.size() << '\n';
    }

    GRAPH[START].EstimatedCost = gg::DIST(GRAPH[START].Position, GRAPH[GOAL].Position);
    GRAPH[START].Status = Type::OPEN;
    OpenList.push(&GRAPH[START]);

    Node* CurrentNode;

    while(OpenList.size() > 0){
        CurrentNode    =   OpenList.top();
        OpenList.pop();

        if(CurrentNode->ID == GOAL) // GOAL
            break;

        std::vector<Connection> Connections = GConnections[CurrentNode->ID];
        for(Connection c : Connections) {
            float Heuristic = 0.f;
            float costToNode = CurrentNode->RealCost + c.Value;
            if (GRAPH[c.To].Status == Type::CLOSED) {

                if(GRAPH[c.To].RealCost <= costToNode)
                    continue;

                GRAPH[c.To].Status = Type::OPEN;
                OpenList.push(&GRAPH[c.To]);

                Heuristic = GRAPH[c.To].EstimatedCost - GRAPH[c.To].RealCost;

            }
            else if (GRAPH[c.To].Status == Type::OPEN)      {
                if(GRAPH[c.To].RealCost <= costToNode)
                    continue;

                Heuristic = GRAPH[c.To].EstimatedCost - GRAPH[c.To].RealCost;
            }
            else {                       //  Heurístic: Euclidean Distance
                Heuristic = costToNode + gg::DIST(GRAPH[c.To].Position, GRAPH[GOAL].Position);
                GRAPH[c.To].Status = Type::OPEN;
                OpenList.push(&GRAPH[c.To]);
            }

            GRAPH[c.To].RealCost = costToNode;
            GRAPH[c.To].Bitconnect = c;
            GRAPH[c.To].EstimatedCost = costToNode + Heuristic;

        } //FOR-LOOP end

        CurrentNode->Status = Type::CLOSED;
    }

    if(CurrentNode->ID != GOAL){
        std::cout << "CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR" << '\n';
    }
    else{
        std::vector<Connection> path;
        while(CurrentNode->ID != START){
            path.push_back(CurrentNode->Bitconnect);
            //std::cout << CurrentNode.Bitconnect.Name << " - ";
            //Waypoint wp(GRAPH[CurrentNode->Bitconnect.To].Position, CurrentNode->ID);
            //Output.push(wp);
            CurrentNode = &GRAPH[CurrentNode->Bitconnect.From];
        }

        std::cout << "CAMINO: " << '\n';

        uint8_t i = path.size();
        while(i--) std::cout << path[i].Name << '-';

        std::cout << '\n';
    }

    printStats();
    std::cout << "-----------------------------------------------" << '\n';
}


float CalculateHeuristic() {


    return 0;
}

uint16_t Pathfinding::getGraphSize(){
    return GRAPH.size();
}

void Pathfinding::printStats(){
    uint16_t OPEN        = 0;
    uint16_t CLOSED      = 0;
    uint16_t UNVISITED   = 0;
    for(uint8_t i = 0; i < GRAPH.size(); ++i){
        if(GRAPH[i].Status == Type::OPEN)
            ++OPEN;
        else if(GRAPH[i].Status == Type::CLOSED)
            ++CLOSED;
        else if(GRAPH[i].Status == Type::UNVISITED)
            ++UNVISITED;
    }
    std::cout << '\n';
    std::cout << "OPEN:      " << OPEN << '\n';
    std::cout << "CLOSED:    " << CLOSED << '\n';
    std::cout << "UNVISITED: " << UNVISITED << '\n' << '\n';
}


void Pathfinding::DroNodes(){
    uint16_t color[4];
    uint8_t i = GRAPH.size();
    while(i--){
        if(GRAPH[i].Status = Type::UNVISITED){
            color[0] = 1;
            color[1] = 50;
            color[2] = 50;
            color[3] = 50;
        }
        else if (GRAPH[i].Status = Type::CLOSED){
            color[0] = 1;
            color[1] = 255;
            color[2] = 10;
            color[3] = 10;
        }
        else{
            color[0] = 1;
            color[1] = 10;
            color[2] = 10;
            color[3] = 255;
        }
        Singleton<GameEngine>::Instance()->Draw3DLine(GRAPH[i].Position, gg::Vector3f(GRAPH[i].Position.X, GRAPH[i].Position.Y + 50, GRAPH[i].Position.Z), color);

    }
}
