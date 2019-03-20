#ifndef _UTIL_H
#define _UTIL_H

#include <cstdint>
//#include <iostream>
#include <glm/glm.hpp>


namespace gg{

    //  ---
    //  This is just used for checking distances between points. It doesn't compute
    //  the sqrt, but:
    //      sqrt(x) < sqrt(y) = x < y   Therefore, the condition remains the same
    //===============================================================================
    float FastDIST(const glm::vec3 &Vector1, const glm::vec3 &Vector2);

    glm::vec3 Direccion2D(glm::vec3 rot);
    glm::vec3 Direccion3D(glm::vec3 rot);
    glm::vec3 Direccion2D_to_rot(glm::vec3 rot);

    float genFloatRandom(float min, float max);
    uint16_t genIntRandom(uint16_t min, uint16_t max);


    struct Color{
        Color();
        Color(uint8_t _R, uint8_t _G, uint8_t _B);
        Color(uint8_t _R, uint8_t _G, uint8_t _B, float _Alpha);
        Color(const Color &orig);

        uint8_t R, G, B;
        float Alpha;
    };

    struct RBActionStruct{
        RBActionStruct();
        RBActionStruct(float,float,float);
        RBActionStruct(const RBActionStruct &orig);


        float vX,vY,vZ;
    };

    void getWeaponInformation(float&, float&, float&, float&, int&, int);
};

//std::ostream& operator<<(std::ostream& os, const glm::vec3 &v1);
//template <typename T>
//T gg::T::operator+ (T v1);

#endif
