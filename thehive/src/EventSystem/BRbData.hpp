#ifndef BRBDATA_H
#define BRBDATA_H

#include "BData.hpp"

class BRbData : public BData {
public:
    BRbData(gg::RBActionStruct _Value);
    BRbData(const BRbData &orig);
    ~BRbData();

    gg::RBActionStruct getRbData();

private:
    gg::RBActionStruct Value;
};

#endif
