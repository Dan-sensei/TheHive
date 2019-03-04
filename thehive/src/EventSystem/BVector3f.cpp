#include "BVector3f.hpp"

BVector3f::BVector3f(glm::vec3 _Value)
:Value(_Value)
{}

BVector3f::BVector3f(const BVector3f &orig){
    Value = orig.Value;
}


BVector3f::~BVector3f(){}


glm::vec3 BVector3f::getVector3f(){
    return Value;
}
