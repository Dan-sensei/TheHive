#include "Blackboard.hpp"
std::map<std::string, BData*> Blackboard::GLOBAL_BDataMap;

Blackboard::Blackboard(){}
Blackboard::Blackboard(const Blackboard &orig){}
Blackboard::~Blackboard(){
    auto it = BDataMap.begin();

    while(it != BDataMap.end()){
        delete it->second;
        ++it;
    };
}

void Blackboard::ClearGlobalBlackboard(){
    auto it = GLOBAL_BDataMap.begin();

    while(it != GLOBAL_BDataMap.end()){
        delete it->second;
        ++it;
    };

}

void Blackboard::setData(const std::string Target, BData* Data){
    auto DataFound = BDataMap.find(Target);

    if(DataFound != BDataMap.end()){
        delete DataFound->second;
        DataFound->second = Data;
    }
    else
        BDataMap.insert(std::make_pair(Target, Data));

}
BData* Blackboard::getBData(const std::string &Target){
    auto DataFound = BDataMap.find(Target);

    if(DataFound != BDataMap.end())
        return DataFound->second;

    return nullptr;
}

void Blackboard::GLOBAL_setData(const std::string Target, BData* Data){
    auto DataFound = GLOBAL_BDataMap.find(Target);

    if(DataFound != GLOBAL_BDataMap.end()){
        delete DataFound->second;
        DataFound->second = Data;
    }
    else
        GLOBAL_BDataMap.insert(std::make_pair(Target, Data));

}
BData* Blackboard::GLOBAL_getBData(const std::string &Target){
    auto DataFound = GLOBAL_BDataMap.find(Target);

    if(DataFound != GLOBAL_BDataMap.end())
        return DataFound->second;

    return nullptr;
}
bool Blackboard::GLOBAL_removeData(const std::string Target){
    auto DataFound = GLOBAL_BDataMap.find(Target);

    if(DataFound != GLOBAL_BDataMap.end()){
        delete DataFound->second;
        GLOBAL_BDataMap.erase(DataFound);
        return true;
    }

    return false;
}
