#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <vector>
#include <stack>
#include <queue>
#include <random>
#include "NavmeshStructs.hpp"
#include <Util.hpp>
#include <Omicron/BillboardBueno.hpp>

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

        void FindPath(const glm::vec3 &START, const glm::vec3 &GOAL, std::stack<Waypoint> &Output);
        void A_Estrella(uint16_t START, uint16_t GOAL, std::stack<Waypoint> &Output);
        void resetGraph();
        void print();

        glm::vec3 getRandomNodePosition();

        void DroNodes();

        void SetDebug(bool flag);
        bool isDebugging();

        void clear();   //  Provisional
    private:
        Pathfinding();
        Pathfinding(const Pathfinding &orig) = delete;
        Pathfinding operator=(const Pathfinding &orig) = delete;

        uint16_t FindClosestNodeOfFace(const glm::vec3 &Position, uint16_t Node);

        std::vector<Node> GRAPH;
        std::vector<std::vector<Connection>> GConnections;
        std::priority_queue<Node*, std::vector<Node*>, Comparator> OpenList;

        std::vector<Face> FACES;

        //Debug
        std::vector<BillboardBueno> IDs;
        std::vector<BillboardBueno> BillboardFaces;
        glm::vec3 Goal;
        bool Debug;
};



#endif
