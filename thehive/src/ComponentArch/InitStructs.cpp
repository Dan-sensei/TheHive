#include "InitStructs.hpp"

InitCTransform::InitCTransform(
    float  _x, float  _y, float  _z,
    float _rx, float _ry, float _rz,
    float _sx, float _sy, float _sz
) :  x(_x),  y(_y),  z(_z),
    rx(_rx), ry(_ry), rz(_rz),
    sx(_sx), sy(_sy), sz(_sz)
{}

InitCRenderable_3D::InitCRenderable_3D(
    const std::string &_pathToModel,
    const Material &mat
) : pathToModel(_pathToModel), material(mat)
{}
