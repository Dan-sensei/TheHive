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
        float calculateDist(uint16_t N1, uint16_t N2);
        void A_Estrella(uint16_t GOAL, std::stack<gg::Vector3f> &Output);
        float CalculateHeuristic();
        void print();

        void DroNodes();

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
