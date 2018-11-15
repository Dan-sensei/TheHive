#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include <cstdint>
#include <vector>
#include <queue>
#include <string>

enum Type{
    OPEN = 0,
    CLOSED,
    UNVISITED
};

struct Connection{
    Connection(uint16_t _From = 0, uint16_t _To = 0, float _Value = 0, std::string _Name = "None");
    Connection(const Connection &orig);
    uint16_t From;
    uint16_t To;
    float Value;
    std::string Name;
};

struct Node{
    Node();
    Node(uint16_t _ID);
    Node(const Node &orig);
    uint16_t ID;
    Connection Bitconnect;
    float RealCost;
    float Heuristic;
    float EstimatedCost;
    Type Status;
};

struct Comparator{
    uint16_t operator() (const Node &N1, const Node &N2);
};

class Pathfinding{
    friend class Comparator;
    public:
        Pathfinding();
        Pathfinding(const Pathfinding &orig);
        ~Pathfinding();

        void A_Estrella();
        float CalculateHeuristic();
        void print();
    private:

        std::vector<Node> GRAPH;
        std::vector<Connection> GConnections[7];
        std::priority_queue<Node, std::vector<Node>, Comparator> OpenList;

};



#endif