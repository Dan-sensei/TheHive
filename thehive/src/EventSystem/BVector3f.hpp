#ifndef BVECTOR3F_H
#define BVECTOR3F_H

#include "BData.hpp"


class BVector3f : public BData {
public:
    BVector3f(glm::vec3 _Value);
    BVector3f(const BVector3f &orig);
    ~BVector3f();

    glm::vec3             getVector3f();

private:
    glm::vec3 Value;
};

#endif
