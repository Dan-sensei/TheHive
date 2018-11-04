#ifndef _INITSTRUCTS_H
#define _INITSTRUCTS_H

#include <string>
#include "Material.hpp"

struct ICTransform{

    ICTransform(
        float  _x, float  _y, float  _z,
        float _rx, float _ry, float _rz,
        float _sx, float _sy, float _sz
    );

    float  x,  y,  z;
    float rx, ry, rz;
    float sx, sy, sz;
};

//struct ICKeyboard{
//
//};

struct ICRenderable_3D{

    ICRenderable_3D(
        const std::string &_pathToModel,
        const Material &mat
    );

    std::string pathToModel;
    Material material;
};


#endif
