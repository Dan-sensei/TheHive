#include "BData.hpp"

BData::BData(){}
BData::BData(const BData &orig){}
BData::~BData(){}


int             BData::getInt(){
    return 0;
}
bool            BData::getBool(){
    return false;
}

float           BData::getFloat(){
    return 0;
}

std::string     BData::getString(){
    return "";
}

glm::vec3    BData::getVector3f(){
    return glm::vec3();
}
