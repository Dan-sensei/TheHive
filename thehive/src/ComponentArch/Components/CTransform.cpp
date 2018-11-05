#include "CTransform.hpp"
#include <iostream>
#include <ComponentArch/ObjectManager.hpp>
#include <Singleton.hpp>
#include <ComponentArch/InitStructs.hpp>


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

void CTransform::initComponent(){}

void CTransform::setPosition(const gg::Vector3f &position){
    x = position.X;
    y = position.Y;
    z = position.Z;
}

void CTransform::setRotation(const gg::Vector3f &rotation){
    rx = rotation.X;
    ry = rotation.Y;
    rz = rotation.Z;
}

void CTransform::setScale(const gg::Vector3f &scale){
    sx = scale.X;
    sy = scale.Y;
    sz = scale.Z;
}

void CTransform::initializeComponentData(const void* data) {

    //  We get a void* to our data, but, since we are on the TRANSFORM component

    //  We cast the void to our InitStructure of the TRANSFORM component
    ICTransform* cData = (ICTransform*)data;

    x = cData->x;
    y = cData->y;
    z = cData->z;

    rx = cData->rx;
    ry = cData->ry;
    rz = cData->rz;

    sx = cData->sx;
    sy = cData->sy;
    sz = cData->sz;
}

//  ---
//  Returns the current position on a GG vector
//==================================================================================
gg::Vector3f CTransform::getPosition(){
    gg::Vector3f currentPositionGG;

    currentPositionGG.X = x;
    currentPositionGG.Y = y;
    currentPositionGG.Z = z;

    return currentPositionGG;
}
