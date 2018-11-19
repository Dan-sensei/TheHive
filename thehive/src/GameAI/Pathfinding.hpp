#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <vector>
#include <stack>
#include <queue>
#include "NavmeshStructs.hpp"
#include <Util.hpp>

template <typename T>
class Singleton;

struct Comparator{
    bool operator() (const Node* N1, const Node* N2);
};

class Pathfinding{
    friend class Comparator;
    friend class Singleton<Pathfinding>;
    public:
        ~Pathfinding();

        void AddConnection(uint16_t From, uint16_t To);
        void A_Estrella(uint16_t START, uint16_t GOAL, std::stack<Waypoint> &Output);
        void A_Estrella2(uint16_t START, uint16_t GOAL, std::stack<Waypoint> &Output);
        void resetGraph();
        float CalculateHeuristic();
        void print();

        void DroNodes();

        uint16_t getGraphSize();

    private:
        Pathfinding();
        Pathfinding(const Pathfinding &orig) = delete;
        Pathfinding operator=(const Pathfinding &orig) = delete;

        void printStats();
        std::vector<Node> GRAPH;
        std::vector<std::vector<Connection>> GConnections;
        std::priority_queue<Node*, std::vector<Node*>, Comparator> OpenList;

};



#endif
