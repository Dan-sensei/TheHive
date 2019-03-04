#include "CTransform.hpp"
#include <iostream>
#include <ComponentArch/ObjectManager.hpp>


CTransform::CTransform(const glm::vec3 &_Position, const glm::vec3 &_Rotation)
:Position(_Position), Rotation(_Rotation)
{}

CTransform::CTransform(const CTransform &orig){
    Position = orig.Position;
    Rotation = orig.Rotation;
}

CTransform::~CTransform(){}


void CTransform::setPosition(const glm::vec3 &_Position){
    Position = _Position;
}

void CTransform::setRotation(const glm::vec3 &_Rotation){
    Rotation = _Rotation;
}

//  ---
//  Returns the current position on a GG vector
//==================================================================================
glm::vec3 CTransform::getPosition(){
    return Position;
}

glm::vec3 CTransform::getRotation(){
    return Rotation;
}
