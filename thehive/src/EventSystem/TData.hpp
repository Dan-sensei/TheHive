
#ifndef _TData_H
#define _TData_H

#include <map>
//#include <iostream>

#include "EventSystem/EnumDataType.hpp"
//#include "Util.hpp"

class TData{
public:
    TData();
    TData(const TData &orig);
    ~TData();

    void add(EnumDataType type,float dato);
    float find(EnumDataType type);

    bool clearData(EnumDataType type);
    void clin();
private:
    std::map <EnumDataType,float>m_dataMap;
};
#endif
