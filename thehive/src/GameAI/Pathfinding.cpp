#include "Pathfinding.hpp"
#include <iostream>
#include <BinaryParser.hpp>
#include "Singleton.hpp"
#include <GameEngine/GameEngine.hpp>
#include <numeric>


//  COMPARATOR
bool Comparator::operator()(const Node* N1, const Node* N2){
    return N1->EstimatedCost > N2->EstimatedCost;
}

Pathfinding::Pathfinding()
:goal(0), DisplayFacesNodes(false), DisplayConnections(false), DisplayNodes(true), DisplayPath(true), DisplayVectors(true)
{

    //bool loaded = Singleton<MeshImporter>::Instance()->importNavmeshV2("assets/NavMeshes/PROTOTIPO_CIUDAD.obj", GRAPH, GConnections, FACES);
    BinaryParser::ReadNavmeshData("assets/BinaryFiles/L4D2Nav.gg", GRAPH, GConnections, FACES);
    //// std::cout << "GRAPH CREATED!" << '\n';

    IDs.resize(GRAPH.size());
    uint16_t i = GRAPH.size();
    while(i--){

        Singleton<GameEngine>::Instance()->createBillboard(IDs[i], GRAPH[i].Position + gg::Vector3f(0, 60, 0));
        IDs[i].setText(std::to_string(i) );
        uint8_t color[4] = {1, 0, 0, 0};
        IDs[i].setColor(color);
    }

}

Pathfinding::~Pathfinding(){

}

void Pathfinding::resetGraph(){
    //// std::cout << "Reseting" << '\n';
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
        //gg::cout("CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR");
        //// std::cout << "CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR" << '\n';
    }
    else{
        uint16_t nodes = 0;
        while(CurrentNode->ID != START) {
            Node* Next = &GRAPH[CurrentNode->Bitconnect.To];
            Output.emplace(Next->Position, Next->ID, Next->Radius);
            CurrentNode = &GRAPH[CurrentNode->Bitconnect.From];
            ++nodes;
        }
        ++nodes;
        gg::cout("PATH = " + std::to_string(nodes) + " NODES", gg::Color(204, 0, 255));
    }
    //printStats();
}

void Pathfinding::FindPath(const gg::Vector3f &START, const gg::Vector3f &GOAL, std::stack<Waypoint> &Output) {

    // std::cout << "SEARCHING!" << '\n';
    uint16_t StartFN, GoalFN;
    //float dist = std::inner_product(p.normal, (vectorSubtract(point, p.point)));
    bool FoundStart = false;
    bool FoundGoal = false;
    for(uint16_t i = 0; i < FACES.size(); ++i) {

        if(!FoundStart){
            if(START.X < FACES[i].TL.X || START.Z > FACES[i].TL.Z)
                goto checkGoal;

            else if(START.X > FACES[i].BR.X || START.Z < FACES[i].BR.Z)
                goto checkGoal;

            StartFN = i;
            FoundStart = true;
        }

        checkGoal:
        if(!FoundGoal){

            if(GOAL.X < FACES[i].TL.X || GOAL.Z > FACES[i].TL.Z)
                continue;

            else if(GOAL.X > FACES[i].BR.X || GOAL.Z < FACES[i].BR.Z)
                continue;

            GoalFN = i;
            FoundGoal = true;
        }

        if(FoundStart && FoundGoal)
            break;
    }

    if(!FoundStart || !FoundGoal){
        gg::cout("El destino no esta en ninguna cara del Navmesh", gg::Color(255, 0, 0, 1));
        return;
    }
    //gg::cout("Start Face = " + std::to_string(StartFN) + " | Goal Face = " + std::to_string(GoalFN));
    goal = GOAL;
    if(StartFN == GoalFN){
        gg::cout("Estan en la misma cara", gg::Color(0, 204, 102));
        Output.emplace(GOAL, 0, 0);
        return;
    }

    uint16_t StartPortal = FindClosestNodeOfFace(GOAL, StartFN);
    uint16_t EndPortal = FindClosestNodeOfFace(START, GoalFN);

    Output.emplace(GOAL, EndPortal, GRAPH[EndPortal].Radius);
    A_Estrella(StartPortal, EndPortal, Output);
    Output.emplace(GRAPH[StartPortal].Position, StartPortal, GRAPH[StartPortal].Radius);

}

uint16_t Pathfinding::FindClosestNodeOfFace(const gg::Vector3f &Position, uint16_t Node){
    auto Iterator = FACES[Node].Portals.begin();
    uint16_t Portal = *Iterator;
    ++Iterator;
    if(Iterator != FACES[Node].Portals.end()){
        float currentDist = gg::FastDIST(Position, GRAPH[Portal].Position);

        while( Iterator != FACES[Node].Portals.end()){
            float newMin = gg::FastDIST(Position, GRAPH[*Iterator].Position);
            if(newMin < currentDist) {
                currentDist = newMin;
                Portal = *Iterator;
            }
            ++Iterator;
        }

    }
    return Portal;
}


void Pathfinding::SwitchDisplayFacesNodes(){
    DisplayFacesNodes = !DisplayFacesNodes;
    if(DisplayFacesNodes && BillboardFaces.empty()){
        BillboardFaces.resize(FACES.size());
        uint16_t j = FACES.size();
        while(j--){
            uint8_t color[4] = {1, 0, 0, 0};

            Singleton<GameEngine>::Instance()->createBillboard(BillboardFaces[j], FACES[j].TL + gg::Vector3f(0, 60+j*2, 0));
            BillboardFaces[j].setText(std::to_string(j));
            BillboardFaces[j].setColor(color);
        }
    }
    else if(!DisplayFacesNodes && !BillboardFaces.empty()){
        BillboardFaces.clear();
    }
}

void Pathfinding::SwitchDisplayConnections(){
    DisplayConnections = !DisplayConnections;
}

void Pathfinding::SwitchDisplayNodes(){
    DisplayNodes = !DisplayNodes;
    if(DisplayNodes && IDs.empty()){
        IDs.resize(GRAPH.size());
        uint16_t i = GRAPH.size();
        while(i--){

            Singleton<GameEngine>::Instance()->createBillboard(IDs[i], GRAPH[i].Position + gg::Vector3f(0, 60, 0));
            IDs[i].setText(std::to_string(i) );
            uint8_t color[4] = {1, 0, 0, 0};
            IDs[i].setColor(color);
        }
    }
    else if(!DisplayNodes && !IDs.empty()){
        IDs.clear();
    }
}

void Pathfinding::SwitchDisplayPath(){
    DisplayPath = !DisplayPath;
}

void Pathfinding::SwitchDisplayVectors(){
    DisplayVectors = !DisplayVectors;
}

// void Pathfinding::printStats(){
//     uint16_t OPEN        = 0;
//     uint16_t CLOSED      = 0;
//     uint16_t UNVISITED   = 0;
//     for(uint8_t i = 0; i < GRAPH.size(); ++i){
//         if(GRAPH[i].Status == Type::OPEN)
//             ++OPEN;
//         else if(GRAPH[i].Status == Type::CLOSED)
//             ++CLOSED;
//         else if(GRAPH[i].Status == Type::UNVISITED)
//             ++UNVISITED;
//     }
//     std::cout << '\n';
//     std::cout << "OPEN:      " << OPEN << '\n';
//     std::cout << "CLOSED:    " << CLOSED << '\n';
//     std::cout << "UNVISITED: " << UNVISITED << '\n' << '\n';
// }


void Pathfinding::DroNodes(){
    gg::Color color;
    uint8_t i = GRAPH.size();
    uint8_t length = 0;

    GameEngine* Engine = Singleton<GameEngine>::Instance();

    if(DisplayNodes){
        while(i--){
            length = 100;

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

            Engine->Draw3DLine(GRAPH[i].Position, gg::Vector3f(GRAPH[i].Position.X, GRAPH[i].Position.Y + length, GRAPH[i].Position.Z), color, 5);

            if(goal.X && goal.Y && goal.Z){
                length = 200;
                color.Alpha = 1;
                color.R = 212;
                color.G = 175;
                color.B = 55;
                Engine->Draw3DLine(goal, goal + gg::Vector3f(0,length,0), color, 5);
            }

        }
    }

    if(DisplayConnections){
        //  Connections
        color.Alpha = 1;
        color.R = 0;
        color.G = 153;
        color.B = 153;
        for(uint16_t i = 0; i < GConnections.size(); ++i){
            for(uint16_t j = 0; j < GConnections[i].size(); ++j){
                Engine->Draw3DLine(GRAPH[GConnections[i][j].From].Position + gg::Vector3f(0, 100, 0), GRAPH[GConnections[i][j].To].Position + gg::Vector3f(0, 100, 0), color, 2);
            }
        }
    }

    if(DisplayFacesNodes){
        // 255,20,147
        color.Alpha = 1;
        color.R = 255;
        color.G = 20;
        color.B = 147;
        for(uint16_t i = 0; i < FACES.size(); ++i){
            Engine->Draw3DLine(FACES[i].TL, FACES[i].TL + gg::Vector3f(0, 100, 0), color, 2);
            Engine->Draw3DLine(FACES[i].BR, FACES[i].BR + gg::Vector3f(0, 100, 0), color, 2);
        }
    }
}

void Pathfinding::clear(){  //  Provisional
    IDs.clear();
    BillboardFaces.clear();
}
