#include "BRbData.hpp"

BRbData::BRbData(gg::RBActionStruct _Value)
:Value(_Value) 
{}

BRbData::BRbData(const BRbData &orig){
    Value = orig.Value;
}


BRbData::~BRbData(){}


gg::RBActionStruct BRbData::getRbData(){
    return Value;
}
