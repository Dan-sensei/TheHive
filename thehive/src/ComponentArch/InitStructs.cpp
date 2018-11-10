#include "InitStructs.hpp"

InitCTransform::InitCTransform(
    float  _x, float  _y, float  _z,
    float _rx, float _ry, float _rz
) :  x(_x),  y(_y),  z(_z),
    rx(_rx), ry(_ry), rz(_rz)
{}

InitCRenderable_3D::InitCRenderable_3D(
    const std::string &_pathToModel,
    const Material &mat
) : pathToModel(_pathToModel), material(mat)
{}

InitCRigidBody::InitCRigidBody(
    float _x,   float _y,   float _z,
    float _sX,  float _sY,  float _sZ,
    float _mass,
    float _iX,  float _iY,  float _iZ
) : x(_x),      y(_y),      z(_z),
    sX(_sX),    sY(_sY),    sZ(_sZ),
    mass(_mass),
    iX(_iX),    iY(_iY),    iZ(_iZ)
{}