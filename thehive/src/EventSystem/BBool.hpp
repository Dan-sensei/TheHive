#ifndef BBOOL_H
#define BBOOL_H

#include "BData.hpp"


class BBool : public BData {
public:
    BBool(bool _Value);
    BBool(const BBool &orig);
    ~BBool();

    bool             getBool();

private:
    bool Value;
};

#endif
