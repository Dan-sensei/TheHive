#include "Util.hpp"
#include <math.h>


//gg::Vector3u8::Vector3u8(uint8_t _X, uint8_t _Y, uint8_t _Z)
//:X(_X),Y(_Y),Z(_Z) {};
//gg::Vector3u8::Vector3u8(const Vector3u8 &orig){
//    X = orig.X;
//    Y = orig.Y;
//    Z = orig.Z;
//}
//
//gg::Vector2u8::Vector2u8(uint8_t _X, uint8_t _Y)
//:X(_X),Y(_Y) {};
//gg::Vector2u8::Vector2u8(const Vector2u8 &orig) {
//    X = orig.X;
//    Y = orig.Y;
//}
//
//
//gg::Vector3u16::Vector3u16(uint16_t _X, uint16_t _Y, uint16_t _Z)
//:X(_X),Y(_Y),Z(_Z) {};
//gg::Vector3u16::Vector3u16(const Vector3u16 &orig){
//    X = orig.X;
//    Y = orig.Y;
//    Z = orig.Z;
//}
//
//gg::Vector2u16::Vector2u16(uint16_t _X, uint16_t _Y)
//:X(_X),Y(_Y) {};
//gg::Vector2u16::Vector2u16(const Vector2u16 &orig){
//    X = orig.X;
//    Y = orig.Y;
//}
//
//gg::Vector3i8::Vector3i8(int8_t _X, int8_t _Y, int8_t _Z)
//:X(_X),Y(_Y),Z(_Z) {};
//gg::Vector3i8::Vector3i8(const Vector3i8 &orig){
//    X = orig.X;
//    Y = orig.Y;
//    Z = orig.Z;
//}
//
//gg::Vector2i8::Vector2i8(int8_t _X, int8_t _Y)
//:X(_X),Y(_Y) {};
//gg::Vector2i8::Vector2i8(const Vector2i8 &orig){
//    X = orig.X;
//    Y = orig.Y;
//}
//
//gg::Vector3i16::Vector3i16(int16_t _X, int16_t _Y, int16_t _Z)
//:X(_X),Y(_Y),Z(_Z) {};
//gg::Vector3i16::Vector3i16(const Vector3i16 &orig){
//    X = orig.X;
//    Y = orig.Y;
//    Z = orig.Z;
//}
//
//gg::Vector2i16::Vector2i16(int16_t _X, int16_t _Y)
//:X(_X),Y(_Y) {};
//gg::Vector2i16::Vector2i16(const Vector2i16 &orig){
//    X = orig.X;
//    Y = orig.Y;
//}

gg::Vector3f::Vector3f(float _X, float _Y, float _Z)
:X(_X),Y(_Y),Z(_Z) {};
gg::Vector3f::Vector3f(const Vector3f &orig){
    X = orig.X;
    Y = orig.Y;
    Z = orig.Z;
}

//gg::Vector2f::Vector2f(float _X, float _Y)
//:X(_X),Y(_Y) {};
//gg::Vector2f::Vector2f(const Vector2f &orig){
//    X = orig.X;
//    Y = orig.Y;
//}

gg::Vector3f gg::Vector3f::operator+ ( const Vector3f &v1){
    return Vector3f( v1.X+X,v1.Y+Y,v1.Z+Z);
}
gg::Vector3f gg::Vector3f::operator- ( const Vector3f &v1){
    return Vector3f( v1.X-X,v1.Y-Y,v1.Z-Z);
}
void gg::Vector3f::operator+= ( const Vector3f &v1){
    X+=v1.X;
    Y+=v1.Y;
    Z+=v1.Z;
}
void gg::Vector3f::operator-= ( const Vector3f &v1){
    X-=v1.X;
    Y-=v1.Y;
    Z-=v1.Z;
}
void gg::Vector3f::operator*= ( const Vector3f &v1){
    X*=v1.X;
    Y*=v1.Y;
    Z*=v1.Z;
}


void gg::Vector3f::operator*= ( const float &v1){
    X*=v1;
    Y*=v1;
    Z*=v1;
}
gg::Vector3f gg::Vector3f::operator* ( const Vector3f &v1){
    return Vector3f( v1.X*X,v1.Y*Y,v1.Z*Z);
}
gg::Vector3f gg::Vector3f::operator* ( const float &v1){
    return Vector3f( v1*X,v1*Y,v1*Z);
}

template <typename T>
float DIST(const T &v1, const T &v2){   return 0; }
template <typename T>
float Modulo(const T &v1){      return 0; }
template <typename T>
T Normalice(T v1){ return v1; }

template <>
float gg::DIST<gg::Vector3f>(const gg::Vector3f &v1, const gg::Vector3f &v2){
    return sqrt(
        (v1.X-v2.X)*(v1.X-v2.X)+
        (v1.Y-v2.Y)*(v1.Y-v2.Y)+
        (v1.Z-v2.Z)*(v1.Z-v2.Z)
    );
}

template <>
float gg::Modulo<gg::Vector3f>(const gg::Vector3f &v1){
    return sqrt(
        (v1.X)*(v1.X)+
        (v1.Y)*(v1.Y)+
        (v1.Z)*(v1.Z)
    );
}

template <>
gg::Vector3f gg::Normalice<gg::Vector3f>(gg::Vector3f v1){
    float modulo=gg::Modulo(v1);
    v1.X=v1.X/modulo;
    v1.Y=v1.Y/modulo;
    v1.Z=v1.Z/modulo;
    return v1;
}


std::ostream& operator<<(std::ostream& os, const gg::Vector3f &v1){
    os << "(" << v1.X<< "," << v1.Y << "," << v1.Z << ")";
    return os;
}
