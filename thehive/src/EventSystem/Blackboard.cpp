#include "Blackboard.hpp"

Blackboard::Blackboard(){}
Blackboard::Blackboard(const Blackboard &orig){}
Blackboard::~Blackboard(){
    auto it = BDataMap.begin();

    while(it != BDataMap.end()){
        delete it->second;
        ++it;
    };
}

void Blackboard::setData(const std::string Target, BData* Data){
    auto DataFound = BDataMap.find(Target);

    if(DataFound != BDataMap.end())
        DataFound->second = Data;
    else
        BDataMap.insert(std::make_pair(Target, Data));

}
BData* Blackboard::getBData(const std::string &Target){
    auto DataFound = BDataMap.find(Target);

    if(DataFound != BDataMap.end())
        return DataFound->second;

    return nullptr;
}
