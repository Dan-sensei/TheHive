#ifndef BLACKBOARD_H
#define BLACKBOARD_H

#include <map>
#include "BData.hpp"
#include "EventSystem/EnumDataType.hpp"
#include <string>


class Blackboard{
public:
    Blackboard();
    Blackboard(const Blackboard &orig);
    ~Blackboard();

    void setData(const std::string Target, BData* Data);
    BData* getBData(const std::string &Target);

private:
    std::map<std::string, BData*> BDataMap;
};

#endif
