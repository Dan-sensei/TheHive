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

    void GLOBAL_setData(const std::string Target, BData* Data);
    BData* GLOBAL_getBData(const std::string &Target);
    bool GLOBAL_removeData(const std::string Target);

    static void ClearGlobalBlackboard();
private:
    std::map<std::string, BData*> BDataMap;
    static std::map<std::string, BData*> GLOBAL_BDataMap;
};

#endif
