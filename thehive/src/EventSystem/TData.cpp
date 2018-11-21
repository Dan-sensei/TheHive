//#include <iostream>
//mio
//#include <cstdlib>
//#include <stdio.h>
//#include <stdlib.h>
//#include <termios.h>
//#include <term.h>
//#include <curses.h>
//#include <unistd.h>
//#include <vector>

#include "EventSystem/TData.hpp"



TData::TData(){
}
TData::~TData(){}

TData::TData(const TData &orig){
    m_dataMap=orig.m_dataMap;
}
float TData::find(EnumDataType type){
    /**
    std::map<char,int> mymap;
 std::map<char,int>::iterator it;

 mymap['a']=50;
 mymap['b']=100;
 mymap['c']=150;
 mymap['d']=200;

 it = mymap.find('b');
 if (it != mymap.end())
   mymap.erase (it);
    **/
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

//template <>
//void TData::add(EnumDataType type,float dato){
//m_dataMap.add(type,dato);
//}
