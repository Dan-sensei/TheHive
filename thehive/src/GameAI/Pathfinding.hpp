#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <vector>
#include <array>
#include <queue>
#include "NavmeshStructs.hpp"

struct Comparator{
    bool operator() (const Node* N1, const Node* N2);
};

class Pathfinding{
    friend class Comparator;
    public:
        Pathfinding();
        Pathfinding(const Pathfinding &orig);
        ~Pathfinding();

        void AddConnection(uint16_t From, uint16_t To);
        float calculateDist(uint16_t N1, uint16_t N2);
        void A_Estrella();
        float CalculateHeuristic();
        void print();
    private:

        void printStats();
        std::vector<Node> GRAPH;
        std::vector<std::vector<Connection>> GConnections;
        std::priority_queue<Node*, std::vector<Node*>, Comparator> OpenList;

};



#endif
