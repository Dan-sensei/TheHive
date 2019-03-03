#include "Util.hpp"
#include <math.h>
#include <random>

#define PI 3.14159265359


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

gg::Vector2f::Vector2f(float _X, float _Y)
:X(_X),Y(_Y) {};
gg::Vector2f::Vector2f(const Vector2f &orig){
    X = orig.X;
    Y = orig.Y;
}

gg::Vector3f gg::Vector3f::operator+ ( const Vector3f &v1){
    return Vector3f( v1.X+X,v1.Y+Y,v1.Z+Z);
}
gg::Vector3f gg::Vector3f::operator- ( const Vector3f &v1){
    return Vector3f( X-v1.X,Y-v1.Y,Z-v1.Z);
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
void gg::Vector3f::operator/= ( const float &divider){
    X/=divider;
    Y/=divider;
    Z/=divider;
}


void gg::Vector3f::operator*= ( const float &v1){
    X*=v1;
    Y*=v1;
    Z*=v1;
}
gg::Vector3f gg::Vector3f::operator* ( const Vector3f &v1) {
    return Vector3f( v1.X*X,v1.Y*Y,v1.Z*Z);
}
gg::Vector3f gg::Vector3f::operator* ( const float &Multiplier) {
    return Vector3f( Multiplier*X, Multiplier*Y, Multiplier*Z);
}
gg::Vector3f gg::Vector3f::operator/ ( const float &divider) {
    return Vector3f( X/divider, Y/divider, Z/divider);
}

bool gg::Vector3f::operator==(const gg::Vector3f &v){
    return (X == v.X && Y == v.Y && Z == v.Z);
}


gg::Vector2f gg::Vector2f::operator* ( const float &Multiplier) {
    return Vector2f( Multiplier*X, Multiplier*Y);
}

float gg::DIST(const gg::Vector3f &Vector1, const gg::Vector3f &Vector2){
    return sqrt(
        (Vector1.X-Vector2.X)*(Vector1.X-Vector2.X)+
        (Vector1.Y-Vector2.Y)*(Vector1.Y-Vector2.Y)+
        (Vector1.Z-Vector2.Z)*(Vector1.Z-Vector2.Z)
    );
}

float gg::FastDIST(const glm::vec3 &Vector1, const glm::vec3 &Vector2){
    return  (Vector1.x-Vector2.x)*(Vector1.x-Vector2.x)+
            (Vector1.y-Vector2.y)*(Vector1.y-Vector2.y)+
            (Vector1.z-Vector2.z)*(Vector1.z-Vector2.z);
}


float gg::Modulo(const gg::Vector3f &Vector){
    return sqrt(
        (Vector.X)*(Vector.X)+
        (Vector.Y)*(Vector.Y)+
        (Vector.Z)*(Vector.Z)
    );
}
float gg::Producto(const gg::Vector3f &dir,const gg::Vector3f &diren){
    return diren.X*dir.X+diren.Y*dir.Y+diren.Z*dir.Z;
}


float gg::Modulo(const gg::Vector2f &Vector){
    return sqrt(
        (Vector.X)*(Vector.X)+
        (Vector.Y)*(Vector.Y)
    );
}

gg::Vector3f gg::Normalice(gg::Vector3f Vector){
    float modulo = gg::Modulo(Vector);
    if(modulo==0){
        return gg::Vector3f();
    }
    else{
        Vector.X = Vector.X/modulo;
        Vector.Y = Vector.Y/modulo;
        Vector.Z = Vector.Z/modulo;
        return Vector;
    }
}
glm::vec3 gg::Direccion2D(glm::vec3 rot){
    glm::vec3 aux = glm::vec3(
         sin(rot.y  *PI/180.f) ,
         0 ,
         cos(rot.y  *PI/180.f)
    );

    return aux;
}
glm::vec3 gg::Direccion3D(glm::vec3 rot){
    glm::vec3 aux = glm::vec3(
        sin(rot.y  *PI/180.f)*(cos(rot.x  *PI/180.f) ) ,
        -sin(rot.x  *PI/180.f) ,
        cos(rot.y  *PI/180.f)*(cos(rot.x  *PI/180.f) )
    );

    return aux;
}
glm::vec3 gg::Direccion2D_to_rot(glm::vec3 rot){
float aux2=asin(rot.x)*180.f/PI;
    if(rot.z<0){
        aux2=180-aux2;
    }
    glm::vec3 aux = glm::vec3(
         0,
         aux2,
         0
    );

    return aux;
}

gg::Vector2f gg::Normalice(gg::Vector2f Vector){
    float modulo = gg::Modulo(Vector);
    Vector.X = Vector.X/modulo;
    Vector.Y = Vector.Y/modulo;
    return Vector;
}

gg::Color::Color()
:R(0), G(0), B(0), Alpha(1)
{}
gg::Color::Color(uint8_t _R, uint8_t _G, uint8_t _B)
:R(_R), G(_G), B(_B), Alpha(1)
{}
gg::Color::Color(uint8_t _R, uint8_t _G, uint8_t _B, float _Alpha)
:R(_R), G(_G), B(_B), Alpha(_Alpha)
{}
gg::Color::Color(const Color &orig){
    R = orig.R;
    G = orig.G;
    B = orig.B;
    Alpha = orig.Alpha;
}

gg::RBActionStruct::RBActionStruct()
:vX(0),vY(0),vZ(0)
{}
gg::RBActionStruct::RBActionStruct(float _vX,float _vY,float _vZ)
:vX(_vX),vY(_vY),vZ(_vZ)
{}
gg::RBActionStruct::RBActionStruct(const RBActionStruct &orig){
    vX = orig.vX;
    vY = orig.vY;
    vZ = orig.vZ;
}

float gg::genFloatRandom(float min, float max){
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::uniform_real_distribution<float> distribution(min, max);

    return distribution(gen);
}

uint16_t gg::genIntRandom(uint16_t min, uint16_t max){
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(gen);
}


// std::ostream& operator<<(std::ostream& os, const gg::Vector3f &v1){
//     os << "(" << v1.X<< "," << v1.Y << "," << v1.Z << ")";
//     return os;
// }
