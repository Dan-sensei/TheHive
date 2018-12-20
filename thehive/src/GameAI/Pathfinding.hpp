#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <vector>
#include <stack>
#include <queue>
#include "NavmeshStructs.hpp"
#include <Util.hpp>
#include <GameEngine/Billboard.hpp>

template <typename T>
class Singleton;

struct Comparator{
    bool operator() (const Node* N1, const Node* N2);
};

class Pathfinding {
    friend class Comparator;
    friend class Singleton<Pathfinding>;
    public:
        ~Pathfinding();

        void FindPath(const gg::Vector3f &START, const gg::Vector3f &GOAL, std::stack<Waypoint> &Output);
        void A_Estrella(uint16_t START, uint16_t GOAL, std::stack<Waypoint> &Output);
        void resetGraph();
        void print();

        void DroNodes();

        bool isDebugging();

        void SwitchDisplayFacesNodes();
        void SwitchDisplayConnections();
        void SwitchDisplayNodes();
        void SwitchDisplayPath();
        void SwitchDisplayVectors();

        inline bool isDisplayPathEnabled()          {    return DisplayPath;         };
        inline bool isDisplayVectorsEnabled()       {    return DisplayVectors;      };
        inline bool isDisplayFacesNodesEnabled()    {    return DisplayFacesNodes;   };
        inline bool isDisplayConnectionsEnabled()   {    return DisplayConnections;  };
        inline bool isDisplayNodesEnabled()         {    return DisplayNodes;        };

        void clear();   //  Provisional
    private:
        Pathfinding();
        Pathfinding(const Pathfinding &orig) = delete;
        Pathfinding operator=(const Pathfinding &orig) = delete;

        uint16_t FindClosestNodeOfFace(const gg::Vector3f &Position, uint16_t Face);

        //void printStats();
        std::vector<Node> GRAPH;
        std::vector<std::vector<Connection>> GConnections;
        std::priority_queue<Node*, std::vector<Node*>, Comparator> OpenList;

        std::vector<Face> FACES;

        //Debug
        std::vector<Billboard> IDs;
        std::vector<Billboard> BillboardFaces;
        uint16_t goal;

        bool DisplayFacesNodes;
        bool DisplayConnections;
        bool DisplayNodes;
        bool DisplayPath;
        bool DisplayVectors;
};



#endif
