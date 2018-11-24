#ifndef BFLOAT_H
#define BFLOAT_H

#include "BData.hpp"


class BFloat : public BData {
public:
    BFloat(float _Value);
    BFloat(const BFloat &orig);
    ~BFloat();

    float             getFloat();

private:
    float Value;
};

#endif
