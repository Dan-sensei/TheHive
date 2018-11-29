#include "EventSystem/TData.hpp"

TData::TData(){}
TData::~TData(){}

TData::TData(const TData &orig){
    m_dataMap=orig.m_dataMap;
}

float TData::find(EnumDataType type){
    return m_dataMap.find(type)->second;
}

void TData::clin(){
    //TRIGGER_MAP::iterator it=m_mapTriggerMap.begin();
    //while(it!=m_mapTriggerMap.end()){
    //    delete(it->second);
    //    ++it;
    //}
}

void TData::add(EnumDataType type,float dato){
    m_dataMap.insert(std::pair<EnumDataType,float>(type,dato));
}

bool TData::clearData(EnumDataType type){
    auto it = m_dataMap.find(type);
    if(it == m_dataMap.end()){
        return false;
    }
    else{
        m_dataMap.erase(it);
        return true;
    }
}


//template <>
//void TData::add(EnumDataType type,float dato){
//m_dataMap.add(type,dato);
//}
