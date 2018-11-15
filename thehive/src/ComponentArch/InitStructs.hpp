#ifndef _INITSTRUCTS_H
#define _INITSTRUCTS_H

#include <string>
#include <GameEngine/Material.hpp>


//  Init Data structs for every component type

struct InitCTransform{

    InitCTransform(
        float  _x, float  _y, float  _z,
        float _rx, float _ry, float _rz
    );

    float  x,  y,  z;
    float rx, ry, rz;
};

//struct ICPlayerController{
//
//};
struct InitCAgent{
    InitCAgent(unsigned long _flags);
    unsigned long flags;
};

struct InitCRenderable_3D{

    InitCRenderable_3D(
        const std::string &_pathToModel,
        const Material &mat
    );

    std::string pathToModel;
    Material material;
};

struct InitCRigidBody{
    InitCRigidBody(
        bool=false, std::string="",
        float=0, float=0, float=0,  // Origen   x,y,z
        float=1, float=1, float=1,  // Tamanyo  sX,sY,sZ
        float=1,                    // Masa     mass
        float=0, float=0, float=0,  // Inercia  iX,iY,iZ
        float=0                     // Friccion
    );

    bool loadedFromPath;
    std::string path;
    float x, y, z;
    float sX,sY,sZ;
    float mass;
    float iX, iY, iZ;
    float friction;
};

struct InitCGun{
    InitCGun(
        float, float, int
    );

    float dmg;
    float cadence;
    int total_bullets;
    // float v_factor;

};


#endif
