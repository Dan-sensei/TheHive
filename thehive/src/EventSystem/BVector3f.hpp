#ifndef BVECTOR3F_H
#define BVECTOR3F_H

#include "BData.hpp"


class BVector3f : public BData {
public:
    BVector3f(gg::Vector3f _Value);
    BVector3f(const BVector3f &orig);
    ~BVector3f();

    gg::Vector3f             getVector3f();

private:
    gg::Vector3f Value;
};

#endif
