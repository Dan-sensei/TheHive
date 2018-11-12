#ifndef _INITSTRUCTS_H
#define _INITSTRUCTS_H

#include <string>
#include <GameEngine/Material.hpp>
#include <EventSystem/EnumTriggerType.hpp>


//  Init Data structs for every component type

struct InitCTransform{

    InitCTransform(
        float  _x, float  _y, float  _z,
        float _rx, float _ry, float _rz
    );

    float  x,  y,  z;
    float rx, ry, rz;
};

//struct ICKeyboard{
//
//};
struct InitCAgent{
    InitCAgent(EnumTriggerType _flags);
    EnumTriggerType flags;
};
struct InitCRenderable_3D{

    InitCRenderable_3D(
        const std::string &_pathToModel,
        const Material &mat
    );

    std::string pathToModel;
    Material material;
};


#endif