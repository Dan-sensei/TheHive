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
:Debug(false)
{

    //bool loaded = Singleton<MeshImporter>::Instance()->importNavmeshV2("assets/NavMeshes/PROTOTIPO_CIUDAD.obj", GRAPH, GConnections, FACES);
    BinaryParser::ReadNavmeshData("assets/BinaryFiles/NavmeshCITY.gg", GRAPH, GConnections, FACES);
    //// std::cout << "GRAPH CREATED!" << '\n';
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
        gg::cout("CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR");
        //// std::cout << "CAMINANTE NO HAY CAMINO SE HACE CAMINO AL ANDAR" << '\n';
    }
    else{
        while(CurrentNode->ID != START) {
            Node* Next = &GRAPH[CurrentNode->Bitconnect.To];
            Output.emplace(Next->Position, Next->ID, Next->Radius);
            CurrentNode = &GRAPH[CurrentNode->Bitconnect.From];
        }
    }
}

void Pathfinding::FindPath(const gg::Vector3f &START, const gg::Vector3f &GOAL, std::stack<Waypoint> &Output) {

    uint16_t StartFN, GoalFN;

    bool FoundStart = false;
    bool FoundGoal = false;
    for(uint16_t i = 0; i < FACES.size(); ++i) {

        if(!FoundStart){
            if(START.X >= FACES[i].TL.X && START.Z <= FACES[i].TL.Z && START.X <= FACES[i].BR.X && START.Z >= FACES[i].BR.Z){
                float FaceYCenter = (FACES[i].TL.Y + FACES[i].BR.Y)/2;
                if(abs(FaceYCenter - START.Y) < 85){
                    StartFN = i;
                    FoundStart = true;
                }
            }
        }

        if(!FoundGoal){
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

    if(!FoundStart || !FoundGoal){
        // gg::cout("El destino no esta en ninguna cara del Navmesh", gg::Color(255, 0, 0, 1));
        return;
    }
    // std::cout << "FOUND IT! Start = " << StartFN << " | Goal " << GoalFN << '\n';

    Goal = GOAL;
    if(StartFN == GoalFN){
        Output.emplace(GOAL, 0, 0);
        return;
    }

    //  They're not in the same face, find wich Node of that face is the closest to the position
    uint16_t StartPortal    =   FindClosestNodeOfFace(START, StartFN);
    uint16_t EndPortal      =   FindClosestNodeOfFace(GOAL, GoalFN);

    Output.emplace(GOAL, EndPortal, GRAPH[EndPortal].Radius);
    A_Estrella(StartPortal, EndPortal, Output);
    Output.emplace(GRAPH[StartPortal].Position, StartPortal, GRAPH[StartPortal].Radius);
}

uint16_t Pathfinding::FindClosestNodeOfFace(const gg::Vector3f &Position, uint16_t Node) {
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

void Pathfinding::DroNodes(){
    if(!Debug) return;
    gg::Color color;
    uint8_t i = GRAPH.size();
    uint8_t length = 0;

    GameEngine* Engine = Singleton<GameEngine>::Instance();

    while(i--){
        length = 50;

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

        Engine->Draw3DLine(GRAPH[i].Position, gg::Vector3f(GRAPH[i].Position.X, GRAPH[i].Position.Y + length, GRAPH[i].Position.Z), color, 4);

        if(Goal.X && Goal.Y && Goal.Z){
            length = 100;
            color.Alpha = 1;
            color.R = 212;
            color.G = 175;
            color.B = 55;
            Engine->Draw3DLine(Goal, Goal + gg::Vector3f(0,length,0), color, 5);
        }
    }

    //  Connections
    // color.Alpha = 1;
    // color.R = 0;
    // color.G = 153;
    // color.B = 153;
    // for(uint16_t i = 0; i < GConnections.size(); ++i){
    //     for(uint16_t j = 0; j < GConnections[i].size(); ++j){
    //         Engine->Draw3DLine(GRAPH[GConnections[i][j].From].Position + gg::Vector3f(0, 40, 0), GRAPH[GConnections[i][j].To].Position + gg::Vector3f(0, 40, 0), color, 2);
    //     }
    // }


    //  255,20,147
    // color.Alpha = 1;
    // color.R = 255;
    // color.G = 20;
    // color.B = 147;
    // for(uint16_t i = 0; i < FACES.size(); ++i){
    //     Engine->Draw3DLine(FACES[i].TL, FACES[i].TL + gg::Vector3f(0, 100, 0), color, 2);
    //     Engine->Draw3DLine(FACES[i].BR, FACES[i].BR + gg::Vector3f(0, 100, 0), color, 2);
    // }
}

void Pathfinding::clear(){  //  Provisional
    IDs.clear();
    BillboardFaces.clear();
}

gg::Vector3f Pathfinding::getRandomNodePosition(){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> distribution(0,GRAPH.size());

    return GRAPH[distribution(gen)].Position;
}
