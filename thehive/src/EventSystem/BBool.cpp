#include "BBool.hpp"

BBool::BBool(bool _Value)
:Value(_Value)
{}

BBool::BBool(const BBool &orig){
    Value = orig.Value;
}


BBool::~BBool(){}


bool BBool::getBool(){
    return Value;
}
