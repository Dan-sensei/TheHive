#include "NavmeshStructs.hpp"

//  CONNECTION  --
Connection::Connection(uint16_t _From, uint16_t _To, float _Value, std::string _Name)
:From(_From), To(_To), Value(_Value), Name(_Name)
{}

Connection::Connection(const Connection &orig) {
    From    =   orig.From;
    To      =   orig.To;
    Value   =   orig.Value;
    Name    =   orig.Name;
}

//  NODE    --
Node::Node()
:ID(UINT16_MAX), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED), X(0.f), Y(0.f), Z(0.f)
{}
Node::Node(uint16_t _ID, float _X, float _Y, float _Z)
:ID(_ID), Bitconnect(), RealCost(0.f), Heuristic(0.f), EstimatedCost(0.f), Status(Type::UNVISITED), X(_X), Y(_Y), Z(_Z)
{}

Node::Node(const Node &orig){
    //std::cout << "Copiando Nodo..." << '\n';

    ID              =   orig.ID;
    Bitconnect      =   orig.Bitconnect;
    RealCost        =   orig.RealCost;
    EstimatedCost   =   orig.EstimatedCost;
    Status          =   orig.Status;
    X               =   orig.X;
    Y               =   orig.Y;
    Z               =   orig.Z;
}

std::ostream& operator<<(std::ostream& os, const Node &N){
    os << "(" << N.X<< "," << N.Y << "," << N.Z << ")";
    return os;
}
