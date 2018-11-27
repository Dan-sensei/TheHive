#include "Pathfinding.hpp"
#include <iostream>
#include "MeshImporter.hpp"
#include "Singleton.hpp"
#include <GameEngine/GameEngine.hpp>


//  COMPARATOR
bool Comparator::operator()(const Node* N1, const Node* N2){
    return N1->EstimatedCost > N2->EstimatedCost;
}

Pathfinding::Pathfinding()
:Debug(false), goal(0)
{

    bool loaded = Singleton<MeshImporter>::Instance()->importNavmeshV2("assets/NavMeshes/L4D2Nav.obj", GRAPH, GConnections);
    for(uint16_t i = 0; i < GConnections.size(); ++i){
        for(uint16_t j = 0; j < GConnections[i].size(); ++j){
            if(GConnections[i][j].Value == 0)
                GConnections[i][j].Value = gg::DIST(GRAPH[GConnections[i][j].From].Position, GRAPH[GConnections[i][j].To].Position);
        }
    }

    //std::cout << "GRAPH CREATED!" << '\n';

    std::cout << " ->" << GRAPH.size() << " Nodes created!" << '\n';
    uint16_t cons;

    for(uint8_t i = 0; i < GRAPH.size(); ++i){
        //std::cout << "  -- " << i << " " << GRAPH[i] << '\n';
    }

    //std::cout << "Connections:" << '\n';
    for(uint16_t i = 0; i < GConnections.size(); ++i){
        //std::cout << "[" << i << "] => ";
        for(uint16_t j = 0; j < GConnections[i].size(); ++j){
            //std::cout << GConnections[i][j].Name << " = " << GConnections[i][j].Value << " | ";
            ++cons;
        }
        //std::cout << '\n';
    }

    std::cout << " ->" << cons << " Connections created!" << '\n';

    //std::cout << "Test" << '\n';
    //GRAPH[0].EstimatedCost = 10;
    //GRAPH[2].EstimatedCost = 20;
    //OpenList.push(&GRAPH[0]);
    //OpenList.push(&GRAPH[1]);

    //std::cout << "ID : " << OpenList.top()->ID << " | ESTIMATED COST = " << OpenList.top()->EstimatedCost << '\n';
}

Pathfinding::~Pathfinding(){

}

void Pathfinding::SetDebug(bool flag){
    Debug = flag;

    if(flag && IDs.empty()){
        IDs.reserve(GRAPH.size());
        uint16_t i = GRAPH.size();
        while(i--){

            Singleton<GameEngine>::Instance()->createBillboard(IDs[i], GRAPH[i].Position + gg::Vector3f(0, 60, 0));
            IDs[i].setText(std::to_string(i) );
            uint8_t color[4] = {1, 0, 0, 0};
            IDs[i].setColor(color);

        }
    }
    else if(!flag && !IDs.empty()){
        IDs.clear();
    }
}

bool Pathfinding::isDebugging(){
    return Debug;
}

void Pathfinding::resetGraph(){
    //std::cout << "Reseting" << '\n';
    uint16_t i = GRAPH.size();
    while(i--){
        GRAPH[i].Status = Type::UNVISITED;
        GRAPH[i].RealCost = 0;
        GRAPH[i].EstimatedCost = 0;
        GRAPH[i].Bitconnect = Connection();
    }
}

void Pathfinding::A_Estrella(uint16_t START, uint16_t GOAL, std::stack<Waypoint> &Output){
    goal = GOAL;
    resetGraph();
    OpenList = std::priority_queue<Node*, std::vector<Node*>, Comparator>();

    //{
    //    uint16_t c = 0;
    //    for(uint16_t i = 0; i < GRAPH.size(); ++i)
    //        if(GRAPH[i].Status == Type::UNVISITED) ++c;

    //    std::cout << "GRAPH UNVISITED: " << c << '\n';
    //    std::cout << "       OPENLIST: " << OpenList.size() << '\n';
    //}

    GRAPH[START].EstimatedCost = gg::DIST(GRAPH[START].Position, GRAPH[GOAL].Position);
    GRAPH[START].Status = Type::OPEN;
    OpenList.push(&GRAPH[START]);

    Node* CurrentNode;

    while(OpenList.size() > 0){
        CurrentNode    =   OpenList.top();
        OpenList.pop();

        if(CurrentNode->ID == GOAL) // GOAL
            break;

        std::vector<Connection>* Connections = &GConnections[CurrentNode->ID];
        for(Connection c : *Connections) {
            float costToNode = CurrentNode->RealCost + c.Value;
            Node* targetNode = &GRAPH[c.To];
            if (targetNode->Status == Type::CLOSED) {

                if(targetNode->RealCost <= costToNode)
                    continue;

                targetNode->Status = Type::OPEN;
                OpenList.push(targetNode);

                targetNode->EstimatedCost = targetNode->EstimatedCost - targetNode->RealCost;

            }
            else if (targetNode->Status == Type::OPEN)      {
                if(targetNode->RealCost <= costToNode)
                    continue;

                targetNode->EstimatedCost = targetNode->EstimatedCost - targetNode->RealCost;
            }
            else {                                       //  Heurístic: Euclidean Distance
                targetNode->EstimatedCost = costToNode + gg::DIST(targetNode->Position, GRAPH[GOAL].Position);
                targetNode->Status = Type::OPEN;
                OpenList.push(targetNode);
            }

            targetNode->RealCost = costToNode;
            targetNode->Bitconnect = c;

        } //FOR-LOOP end

        CurrentNode->Status = Type::CLOSED;
    }

    if(CurrentNode->ID != GOAL){
        //std::cout << "CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR" << '\n';
    }
    else{
        Funneling(CurrentNode, START, Output);
    }

    printStats();
}

void Pathfinding::Funneling(Node* CurrentNode, uint16_t START, std::stack<Waypoint> &Output){

    while(CurrentNode->ID != START) {
        //path.push_back(CurrentNode->Bitconnect);
        Node* Next = &GRAPH[CurrentNode->Bitconnect.To];
        Output.emplace(Next->Position, CurrentNode->ID, Next->Radius);
        CurrentNode = &GRAPH[CurrentNode->Bitconnect.From];
        //std::cout << "CAMINO: " << '\n';


        //std::cout << '\n';
    }

}

float funnelCheck (gg::Vector3f origin, gg::Vector3f current, gg::Vector3f target){
    gg::Vector3f oc = current - origin;
    gg::Vector3f ot =  target - origin;
    return ot.X*oc.Y*0;
}

uint16_t Pathfinding::getGraphSize(){
    return GRAPH.size()-1;
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
    //std::cout << '\n';
    //std::cout << "OPEN:      " << OPEN << '\n';
    //std::cout << "CLOSED:    " << CLOSED << '\n';
    //std::cout << "UNVISITED: " << UNVISITED << '\n' << '\n';
}


void Pathfinding::DroNodes(){
    if(!Debug) return;
    gg::Color color;
    uint8_t i = GRAPH.size();
    uint8_t length = 50;
    while(i--){
        if(i==goal){
             length = 100;
             color.Alpha = 1;
             color.R = 212;
             color.G = 175;
             color.B = 55;
             goto dro;
        }
        else length = 50;

        if(GRAPH[i].Status == Type::UNVISITED){
            color.Alpha = 1;
            color.R = 50;
            color.G = 50;
            color.B = 50;
        }
        else if (GRAPH[i].Status == Type::CLOSED){
            color.Alpha = 1;
            color.R = 204;
            color.G = 51;
            color.B = 10;
        }
        else{
            color.Alpha = 1;
            color.R = 0;
            color.G = 102;
            color.B = 204;
        }
        dro:
        Singleton<GameEngine>::Instance()->Draw3DLine(GRAPH[i].Position, gg::Vector3f(GRAPH[i].Position.X, GRAPH[i].Position.Y + length, GRAPH[i].Position.Z), color, 5);

    }

    //  Connections
    color.Alpha = 1;
    color.R = 0;
    color.G = 153;
    color.B = 153;
    for(uint16_t i = 0; i < GConnections.size(); ++i){
        for(uint16_t j = 0; j < GConnections[i].size(); ++j){
            Singleton<GameEngine>::Instance()->Draw3DLine(GRAPH[GConnections[i][j].From].Position + gg::Vector3f(0, 20, 0), GRAPH[GConnections[i][j].To].Position + gg::Vector3f(0, 20, 0), color, 2);
        }
    }
}