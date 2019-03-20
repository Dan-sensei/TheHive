#include "Util.hpp"
#include <math.h>
#include <random>

#define PI 3.14159265359

float gg::FastDIST(const glm::vec3 &Vector1, const glm::vec3 &Vector2){
    return  (Vector1.x-Vector2.x)*(Vector1.x-Vector2.x)+
            (Vector1.y-Vector2.y)*(Vector1.y-Vector2.y)+
            (Vector1.z-Vector2.z)*(Vector1.z-Vector2.z);
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

void gg::getWeaponInformation(float& dmg, float& cdc, float& relDT, float& rng, int& tb, int _type, std::string& sonido_disparo,std::string& sonido_recarga,std::string& sonido_desenfundado, std::string& sonido_vacia){
    switch (_type){
        case 0:
            // Rifle
            dmg = 0.7;
            cdc = 7;
            tb  = 30;
            relDT = 1;
            rng = 0.7;

            sonido_disparo = "event:/SFX/Armas/Rifle/RifleDisparo";
            sonido_recarga = "event:/SFX/Armas/Rifle/RifleRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Rifle/RifleDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Rifle/RifleVacio";

            break;
        case 1:
            // Escopeta
            dmg = 0.8;
            cdc = 1;
            tb  = 10;
            relDT = 3;
            rng = 0.4;

            sonido_disparo = "event:/SFX/Armas/Escopeta/EscopetaDisparo";
            sonido_recarga = "event:/SFX/Armas/Escopeta/EscopetaRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Escopeta/EscopetaDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Escopeta/EscopetaVacia";

            break;
        case 2:
            // Ametralladora
            dmg = 0.3;
            cdc = 9;
            tb  = 100;
            relDT = 6;
            rng = 0.7;

            sonido_disparo = "event:/SFX/Armas/Ametralladora/AmetralladoraDisparo";
            sonido_recarga = "event:/SFX/Armas/Ametralladora/AmetralladoraRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Ametralladora/AmetralladoraDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Ametralladora/AmetralladoraVacia";

            break;
        case 3:
            // Pistola
            dmg = 0.4;
            cdc = 5;
            tb  = 15;
            relDT = 0.5;
            rng = 0.5;

            sonido_disparo = "event:/SFX/Armas/Pistola/PistolaDisparo";
            sonido_recarga = "event:/SFX/Armas/Pistola/PistolaRecarga";
            sonido_desenfundado ="event:/SFX/Armas/Pistola/PistolaDesenfundado";
            sonido_vacia ="event:/SFX/Armas/Pistola/PistolaVacia";

            break;
        case 4:
            // Katana
            dmg = 1;
            cdc = 0.5;
            tb  = -1;
            relDT = -1;
            rng = 0.1;

            break;
    }

    //gg::cout(" --- GUN PICKED --- ");
    //gg::cout(" - - DMG= "       + std::to_string(dmg));
    //gg::cout(" - - CADENCE= "   + std::to_string(cdc));
    //gg::cout(" - - BULLETS= "   + std::to_string(tb));
    //gg::cout(" - - DT= "        + std::to_string(relDT));
    //gg::cout(" - - RANGE= "     + std::to_string(rng));
    //gg::cout(" ------------------ ");

}

// std::ostream& operator<<(std::ostream& os, const glm::vec3 &v1){
//     os << "(" << v1.x<< "," << v1.y << "," << v1.z << ")";
//     return os;
// }
