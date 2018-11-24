#include "BInt.hpp"

BInt::BInt(int _Value)
:Value(_Value)
{}

BInt::BInt(const BInt &orig){
    Value = orig.Value;
}


BInt::~BInt(){}


int BInt::getInt(){
    return Value;
}
