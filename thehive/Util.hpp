#ifndef _UTIL_H
#define _UTIL_H

#include <cstdint>
namespace gg{

    /*          UNSIGNED INT - 8 BITS       */
    struct Vector2u8{
        Vector2u8(uint8_t _X = 0, uint8_t _Y = 0)
        :X(_X),Y(_Y) {};

        uint8_t X, Y;
    };

    struct Vector3u8{
        Vector3u8(uint8_t _X = 0, uint8_t _Y = 0, uint8_t _Z = 0)
        :X(_X),Y(_Y),Z(_Z) {};

        uint8_t X, Y, Z;
    };



    /*          UNSIGNED INT - 16 BITS       */
    struct Vector3u16{
        Vector3u16(uint16_t _X = 0, uint16_t _Y = 0, uint16_t _Z = 0)
        :X(_X),Y(_Y),Z(_Z) {};

        uint16_t X, Y, Z;
    };

    struct Vector2u16{
        Vector2u16(uint16_t _X = 0, uint16_t _Y = 0)
        :X(_X),Y(_Y) {};

        uint16_t X, Y;
    };



    /*          INT - 8 BITS       */
    struct Vector3i8{
        Vector3i8(int8_t _X = 0, int8_t _Y = 0, int8_t _Z = 0)
        :X(_X),Y(_Y),Z(_Z) {};
        int8_t X, Y, Z;
    };

    struct Vector2i8{
        Vector2i8(int8_t _X = 0, int8_t _Y = 0)
        :X(_X),Y(_Y) {};

        int8_t X, Y;
    };



    /*          INT - 16 BITS       */
    struct Vector3i16{
        Vector3i16(int16_t _X = 0, int16_t _Y = 0, int16_t _Z = 0)
        :X(_X),Y(_Y),Z(_Z) {};

        int16_t X, Y, Z;
    };

    struct Vector2i16{
        Vector2i16(int16_t _X = 0, int16_t _Y = 0)
        :X(_X),Y(_Y) {};

        int16_t X, Y;
    };



    /*          FLOAT       */
    struct Vector3f{
        Vector3f(float _X = 0, float _Y = 0, float _Z = 0)
        :X(_X),Y(_Y),Z(_Z) {};

        float X, Y, Z;
    };

    struct Vector2f{
        Vector2f(float _X = 0, float _Y = 0)
        :X(_X),Y(_Y) {};

        float X, Y;
    };


}

#endif
