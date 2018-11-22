#include "NavmeshStructs.hpp"

//  CONNECTION  --
Connection::Connection(uint16_t _From, uint16_t _To, float _Value, const gg::Vector3f &_Vertex1, const gg::Vector3f &_Vertex2)
:From(_From), To(_To), Value(_Value), Vertex1(_Vertex1), Vertex2(_Vertex2)
{}

Connection::Connection(const Connection &orig) {
    From    =   orig.From;
    To      =   orig.To;
    Value   =   orig.Value;
    Vertex1 =   orig.Vertex1;
    Vertex2 =   orig.Vertex2;
}

//  NODE    --
Node::Node()
:ID(UINT16_MAX), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED), Radius(0)
{}
Node::Node(uint16_t _ID, const gg::Vector3f &_Position, float _Radius)
:ID(_ID), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Radius(_Radius), Status(Type::UNVISITED), Position(_Position)
{}

Node::Node(const Node &orig){
    //std::cout << "Copiando Nodo..." << '\n';

    ID              =   orig.ID;
    Bitconnect      =   orig.Bitconnect;
    RealCost        =   orig.RealCost;
    EstimatedCost   =   orig.EstimatedCost;
    Status          =   orig.Status;
    Position        =   orig.Position;
    Radius          =   orig.Radius;
}

//  WAYPOINT
Waypoint::Waypoint()
:ID(0)
{}

Waypoint::Waypoint(const gg::Vector3f &_Position, uint16_t _ID, float _Radius)
:Position(_Position), ID(_ID), Radius(_Radius)
{}

Waypoint::Waypoint(const Waypoint &orig){
    Position = orig.Position;
    ID = orig.ID;
    Radius = orig.Radius;
}

std::ostream& operator<<(std::ostream& os, const Node &N){
    os << "(" << N.Position.X<< "," << N.Position.Y << "," << N.Position.Z << ")";
    return os;
}
