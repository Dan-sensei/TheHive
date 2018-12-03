#include "BVector3f.hpp"

BVector3f::BVector3f(gg::Vector3f _Value)
:Value(_Value)
{}

BVector3f::BVector3f(const BVector3f &orig){
    Value = orig.Value;
}


BVector3f::~BVector3f(){}


gg::Vector3f BVector3f::getVector3f(){
    return Value;
}
