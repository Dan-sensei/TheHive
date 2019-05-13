#include "CTransform.hpp"
#include <iostream>
#include <ComponentArch/ObjectManager.hpp>


CTransform::CTransform(const glm::vec3 &_Position, const glm::quat &_Rotation)
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

void CTransform::setRotation(const glm::quat &_Rotation){
    Rotation = _Rotation;
}

glm::quat CTransform::rotate(const float &Angle_RADs, const glm::vec3 &Axis){
    Rotation = glm::rotate(Rotation, Angle_RADs, Axis);
    return Rotation;
}


//  ---
//  Returns the current position on a GG vector
//==================================================================================
glm::vec3 CTransform::getPosition(){
    return Position;
}

glm::quat CTransform::getRotation(){
    return Rotation;
}
