#include "NavmeshStructs.hpp"

//  FACES
Face::Face(const gg::Vector3f _TL, const gg::Vector3f _BR)
:TL(_TL), BR(_BR)
{}

Face::Face(const Face &orig){
    Portals =   orig.Portals;
    TL      =   orig.TL;
    BR      =   orig.BR;
}



//  CONNECTION  --
Connection::Connection(float _Value, uint16_t _From, uint16_t _To/*, const gg::Vector3f &_Vertex1, const gg::Vector3f &_Vertex2*/)
: Value(_Value), From(_From), To(_To)//, Vertex1(_Vertex1), Vertex2(_Vertex2)
{}

Connection::Connection(const Connection &orig) {
    From    =   orig.From;
    To      =   orig.To;
    Value   =   orig.Value;
    //Vertex1 =   orig.Vertex1;
    //Vertex2 =   orig.Vertex2;
}

//  NODE    --
Node::Node()
:ID(UINT16_MAX), NODE_1(UINT16_MAX), NODE_2(UINT16_MAX), Bitconnect(), RealCost(0.f), EstimatedCost(0.f), Status(Type::UNVISITED), Radius(0)
{}
Node::Node(uint16_t _ID, uint16_t _NODE_1, uint16_t _NODE_2, const gg::Vector3f &_Position, float _Radius)
:ID(_ID), NODE_1(_NODE_1), NODE_2(_NODE_2), Bitconnect(), RealCost(0.f), EstimatedCost(0.f), Radius(_Radius), Status(Type::UNVISITED), Position(_Position)
{}

Node::Node(const Node &orig){
    //// std::cout << "Copiando Nodo..." << '\n';

    Bitconnect      =   orig.Bitconnect;
    RealCost        =   orig.RealCost;
    EstimatedCost   =   orig.EstimatedCost;
    Status          =   orig.Status;
    Position        =   orig.Position;
    Radius          =   orig.Radius;
    ID              =   orig.ID;
    NODE_1          =   orig.NODE_1;
    NODE_2          =   orig.NODE_2;
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
    os << "ID: " << N.ID <<  "   - Face: " << N.NODE_1 << " | " << N.NODE_2 << "    --> (" << N.Position.X<< "," << N.Position.Y << "," << N.Position.Z << ")";
    return os;
}
