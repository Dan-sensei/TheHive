#ifndef _CTRANSFORM_H
#define _CTRANSFORM_H

#include "IComponent.hpp"

class CTransform : public IComponent{
public:
    CTransform();
    CTransform(const CTransform &orig);
    virtual ~CTransform();

    static void initComponent();

    virtual gg::EMessageStatus processMessage();



private:
    float  x,  y,  z;
    float rx, ry, rz;
    float sx, sy, sz;

};

#endif
