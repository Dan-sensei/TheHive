#include "CTransform.hpp"
#include <iostream>
#include <ComponentArch/ObjectManager.hpp>


CTransform::CTransform(const gg::Vector3f &Position, const gg::Vector3f &Rotation)
:x(Position.X),  y(Position.Y),  z(Position.Z),
rx(Rotation.X), ry(Rotation.Y), rz(Rotation.Z)
{
}

CTransform::CTransform(const CTransform &orig){
    x = orig.x;
    y = orig.y;
    z = orig.z;

    rx = orig.rx;
    ry = orig.ry;
    rz = orig.rz;
}

CTransform::~CTransform(){}

void CTransform::initComponent(){

}

void CTransform::Init(){

}


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

gg::Vector3f CTransform::getRotation(){
    gg::Vector3f currentRotationGG;

    currentRotationGG.X = rx;
    currentRotationGG.Y = ry;
    currentRotationGG.Z = rz;

    return currentRotationGG;
}

