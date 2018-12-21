#include "CTransform.hpp"
#include <iostream>
#include <ComponentArch/ObjectManager.hpp>


CTransform::CTransform(const gg::Vector3f &_Position, const gg::Vector3f &_Rotation)
:Position(_Position), Rotation(_Rotation)
{}

CTransform::CTransform(const CTransform &orig){
    Position = orig.Position;
    Rotation = orig.Rotation;
}

CTransform::~CTransform(){}


void CTransform::setPosition(const gg::Vector3f &_Position){
    Position = _Position;
}

void CTransform::setRotation(const gg::Vector3f &_Rotation){
    Rotation = _Rotation;
}
