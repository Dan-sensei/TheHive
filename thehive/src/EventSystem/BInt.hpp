#ifndef BINT_H
#define BINT_H

#include "BData.hpp"


class BInt : public BData {
public:
    BInt(int _Value);
    BInt(const BInt &orig);
    ~BInt();

    int             getInt();

private:
    int Value;
};

#endif
