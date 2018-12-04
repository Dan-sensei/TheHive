#include "Pathfinding.hpp"
#include <iostream>
#include "MeshImporter.hpp"
#include "Singleton.hpp"
#include <GameEngine/GameEngine.hpp>
#include <numeric>


//  COMPARATOR
bool Comparator::operator()(const Node* N1, const Node* N2){
    return N1->EstimatedCost > N2->EstimatedCost;
}

Pathfinding::Pathfinding()
:Debug(false), goal(0)
{

    bool loaded = Singleton<MeshImporter>::Instance()->importNavmeshV2("assets/NavMeshes/L4D2Nav.obj", GRAPH, GConnections, FACES);
    for(uint16_t i = 0; i < GConnections.size(); ++i){
        for(uint16_t j = 0; j < GConnections[i].size(); ++j){
            if(GConnections[i][j].Value == 0)
                GConnections[i][j].Value = gg::DIST(GRAPH[GConnections[i][j].From].Position, GRAPH[GConnections[i][j].To].Position);
        }
    }

    //std::cout << "GRAPH CREATED!" << '\n';

    std::cout << " ->" << GRAPH.size() << " Nodes created!" << '\n';

    for(uint16_t i = 0; i < GRAPH.size(); ++i){
        std::cout << "  -- " << i << " = " << GRAPH[i] << '\n';
    }

    uint16_t cons = 0;
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
    std::cout << " ->" << FACES.size() << " Faces created!" << '\n';
    for(uint16_t i = 0; i < FACES.size(); ++i){
        std::cout << "   Face " << i << "  | P: ";
        for(uint16_t j = 0; j < FACES[i].Portals.size(); ++j)
            std::cout << " " << FACES[i].Portals[j];
        std::cout << '\n';
    }
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
        IDs.resize(GRAPH.size());
        uint16_t i = GRAPH.size();
        while(i--){

            Singleton<GameEngine>::Instance()->createBillboard(IDs[i], GRAPH[i].Position + gg::Vector3f(0, 60, 0));
            IDs[i].setText(std::to_string(i) );
            uint8_t color[4] = {1, 0, 0, 0};
            IDs[i].setColor(color);
        }

        BillboardFaces.resize(FACES.size());
        uint16_t j = FACES.size();
        while(j--){
            uint8_t color[4] = {1, 0, 0, 0};

            Singleton<GameEngine>::Instance()->createBillboard(BillboardFaces[j], FACES[j].TL + gg::Vector3f(0, 60+j*2, 0));
            BillboardFaces[j].setText(std::to_string(j));
            BillboardFaces[j].setColor(color);
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

    GRAPH[START].EstimatedCost = gg::FastDIST(GRAPH[START].Position, GRAPH[GOAL].Position);
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
            float Heuristic = 0;
            Node* targetNode = &GRAPH[c.To];

            bool isOpenNode = false;

            if (targetNode->Status == Type::CLOSED) {

                if(targetNode->RealCost <= costToNode)
                    continue;

                targetNode->Status = Type::OPEN;
                Heuristic = targetNode->EstimatedCost - targetNode->RealCost;
            }
            else if (targetNode->Status == Type::OPEN)      {
                if(targetNode->RealCost <= costToNode)
                    continue;

                isOpenNode = true;
                Heuristic = targetNode->EstimatedCost - targetNode->RealCost;
            }
            else {          //  Heurístic: Euclidean Distance^2
                Heuristic = gg::FastDIST(targetNode->Position, GRAPH[GOAL].Position);
                targetNode->Status = Type::OPEN;
            }

            targetNode->RealCost = costToNode;
            targetNode->EstimatedCost = costToNode + Heuristic;
            targetNode->Bitconnect = c;

            if(!isOpenNode) OpenList.push(targetNode);
        } //FOR-LOOP end

        CurrentNode->Status = Type::CLOSED;
    }

    if(CurrentNode->ID != GOAL) {
        gg::cout("CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR");
    }
    else{
        uint16_t nodes = 0;
        while(CurrentNode->ID != START) {
            Node* Next = &GRAPH[CurrentNode->Bitconnect.To];
            Output.emplace(Next->Position, CurrentNode->ID, Next->Radius);
            CurrentNode = &GRAPH[CurrentNode->Bitconnect.From];
            ++nodes;
        }
        gg::cout("PATH " + std::to_string(nodes));
    }

    printStats();
}

void Pathfinding::FindPath(const gg::Vector3f &START, const gg::Vector3f &GOAL, std::stack<Waypoint> &Output) {

    std::cout << "SEARCHING!" << '\n';
    uint16_t StartFN, GoalFN;
    //float dist = std::inner_product(p.normal, (vectorSubtract(point, p.point)));
    bool FoundStart = false;
    bool FoundGoal = false;
    uint16_t CHECKEDSTART = 0;
    uint16_t CHECKEDEND = 0;

    //  SEARCHING! Wich face is the position of the Agent and the goal
    for(uint16_t i = 0; i < FACES.size(); ++i) {

        if(!FoundStart){
            ++CHECKEDSTART;
            if(START.X >= FACES[i].TL.X && START.Z <= FACES[i].TL.Z && START.X <= FACES[i].BR.X && START.Z >= FACES[i].BR.Z){
                float FaceYCenter = (FACES[i].TL.Y + FACES[i].BR.Y)/2;
                if(abs(FaceYCenter - START.Y) < 85){
                    StartFN = i;
                    FoundStart = true;
                }
            }
        }

        if(!FoundGoal){
            ++CHECKEDEND;
            if(GOAL.X >= FACES[i].TL.X && GOAL.Z <= FACES[i].TL.Z && GOAL.X <= FACES[i].BR.X && GOAL.Z >= FACES[i].BR.Z){
                float FaceYCenter = (FACES[i].TL.Y + FACES[i].BR.Y)/2;
                if(abs(FaceYCenter - GOAL.Y) < 85){
                    GoalFN = i;
                    FoundGoal = true;
                }
            }
        }

        if(FoundStart && FoundGoal) break;
    }

    std::cout << "Found START in " << CHECKEDSTART << '\n';
    gg::cout(std::to_string(CHECKEDSTART) + " FACES CHECKED UNTIL START FOUND!");

    std::cout << "Found GOAL in " << CHECKEDEND << '\n';
    gg::cout(std::to_string(CHECKEDEND) + " FACES CHECKED UNTIL GOAL FOUND!");

    if(!FoundStart || !FoundGoal){
        gg::cout("LA POSICION DEL JUGADOR O GOAL, NO ESTÁN EN NINGUN POLÍGONO", gg::Color(255, 0, 0, 1));
        return;
    }
    std::cout << "FOUND IT! Start = " << StartFN << " | Goal " << GoalFN << '\n';

    //  They're in the same face, just go directly
    if(StartFN == GoalFN){
        Output.emplace(START, 0, 0);
        return;
    }

    //  They're not in the same face, find wich Node of that face is the closest to the position
    uint16_t StartPortal = FACES[StartFN].Portals[0];
    if(FACES[StartFN].Portals.size() > 1){
        float currentDist = gg::FastDIST(START, GRAPH[FACES[StartFN].Portals[0]].Position);
        for(uint16_t i = 1; i < FACES[StartFN].Portals.size(); ++i){
            float newMin = gg::FastDIST(START, GRAPH[FACES[StartFN].Portals[i]].Position);
            if(newMin < currentDist) {
                currentDist = newMin;
                StartPortal = FACES[StartFN].Portals[i];
            }
        }
    }

    //  Same with the goal
    uint16_t EndPortal = FACES[GoalFN].Portals[0];
    if(FACES[GoalFN].Portals.size() > 1){
        float currentDist = gg::FastDIST(GOAL, GRAPH[FACES[GoalFN].Portals[0]].Position);
        for(uint16_t i = 1; i < FACES[GoalFN].Portals.size(); ++i){
            float newMin = gg::FastDIST(GOAL, GRAPH[FACES[GoalFN].Portals[i]].Position);
            if(newMin < currentDist) {
                currentDist = newMin;
                EndPortal = FACES[GoalFN].Portals[i];
            }
        }
    }

    //  Put destination coordinates as last Waypoint
    Output.emplace(GOAL, EndPortal, GRAPH[EndPortal].Radius);
    A_Estrella(StartPortal, EndPortal, Output);
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

    GameEngine* Engine = Singleton<GameEngine>::Instance();

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
        Engine->Draw3DLine(GRAPH[i].Position, gg::Vector3f(GRAPH[i].Position.X, GRAPH[i].Position.Y + length, GRAPH[i].Position.Z), color, 5);

    }

    //  Connections
    color.Alpha = 1;
    color.R = 0;
    color.G = 153;
    color.B = 153;
    for(uint16_t i = 0; i < GConnections.size(); ++i){
        for(uint16_t j = 0; j < GConnections[i].size(); ++j){
            Engine->Draw3DLine(GRAPH[GConnections[i][j].From].Position + gg::Vector3f(0, 20, 0), GRAPH[GConnections[i][j].To].Position + gg::Vector3f(0, 20, 0), color, 2);
        }
    }


    //  255,20,147
    color.Alpha = 1;
    color.R = 255;
    color.G = 20;
    color.B = 147;
    for(uint16_t i = 0; i < FACES.size(); ++i){
        Engine->Draw3DLine(FACES[i].TL, FACES[i].TL + gg::Vector3f(0, 100, 0), color, 2);
        Engine->Draw3DLine(FACES[i].BR, FACES[i].BR + gg::Vector3f(0, 100, 0), color, 2);
    }
}

void Pathfinding::clear(){  //  Provisional
    IDs.clear();
    BillboardFaces.clear();
}
