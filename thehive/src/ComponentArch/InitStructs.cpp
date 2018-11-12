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
InitCAgent::InitCAgent(
    EnumTriggerType _flags
) : flags(_flags)
{}
