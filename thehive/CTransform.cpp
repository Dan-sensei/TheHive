#include "CTransform.hpp"
#include <iostream>
#include "ObjectManager.hpp"
#include "Singleton.hpp"


CTransform::CTransform()
:x(0),  y(0),  z(0),
rx(0), ry(0), rz(0),
sx(0), sy(0), sz(0)
{

}

CTransform::CTransform(const CTransform &orig){
    x = orig.x;
    y = orig.y;
    z = orig.z;

    rx = orig.rx;
    ry = orig.ry;
    rz = orig.rz;

    sx = orig.sx;
    sy = orig.sy;
    sz = orig.sz;
}

CTransform::~CTransform(){

}

void CTransform::initComponent(){
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::TRANSFORM, gg::M_UPDATE);

}

gg::EMessageStatus CTransform::processMessage(){
    std::cout << "UPDATING TRANSFORM COMPONENT!" << '\n';

    return gg::ST_TRUE;
}
