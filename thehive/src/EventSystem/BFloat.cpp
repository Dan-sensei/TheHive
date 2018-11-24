#include "BFloat.hpp"

BFloat::BFloat(float _Value)
:Value(_Value)
{}

BFloat::BFloat(const BFloat &orig){
    Value = orig.Value;
}


BFloat::~BFloat(){}


float BFloat::getFloat(){
    return Value;
}
