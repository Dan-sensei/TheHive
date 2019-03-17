#ifndef _UTIL_H
#define _UTIL_H

#include <cstdint>
#include <iostream>
#include <glm/glm.hpp>


namespace gg{

    /*          UNSIGNED INT - 8 BITS       */
    //struct Vector3u8{
    //    Vector3u8(uint8_t _X = 0, uint8_t _Y = 0, uint8_t _Z = 0);
    //    Vector3u8(const Vector3u8 &orig);

    //    uint8_t X, Y, Z;
    //};

    //struct Vector2u8{
    //    Vector2u8(uint8_t _X = 0, uint8_t _Y = 0);
    //    Vector2u8(const Vector2u8 &orig);

    //    uint8_t X, Y;
    //};



    ///*          UNSIGNED INT - 16 BITS       */
    //struct Vector3u16{
    //    Vector3u16(uint16_t _X = 0, uint16_t _Y = 0, uint16_t _Z = 0);
    //    Vector3u16(const Vector3u16 &orig);

    //    uint16_t X, Y, Z;
    //};

    //struct Vector2u16{
    //    Vector2u16(uint16_t _X = 0, uint16_t _Y = 0);
    //    Vector2u16(const Vector2u16 &orig);

    //    uint16_t X, Y;
    //};



    ///*          INT - 8 BITS       */
    //struct Vector3i8{
    //    Vector3i8(int8_t _X = 0, int8_t _Y = 0, int8_t _Z = 0);
    //    Vector3i8(const Vector3i8 &orig);

    //    int8_t X, Y, Z;
    //};

    //struct Vector2i8{
    //    Vector2i8(int8_t _X = 0, int8_t _Y = 0);
    //    Vector2i8(const Vector2i8 &orig);

    //    int8_t X, Y;
    //};



    /*          INT - 16 BITS       */
    //struct Vector3i16{
    //    Vector3i16(int16_t _X = 0, int16_t _Y = 0, int16_t _Z = 0);
    //    Vector3i16(const Vector3i16 &orig);

    //    int16_t X, Y, Z;
    //};

    //struct Vector2i16{
    //    Vector2i16(int16_t _X = 0, int16_t _Y = 0);
    //    Vector2i16(const Vector2i16 &orig);

    //    int16_t X, Y;
    //};

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
