#include "ZStaticSpotLight.hpp"

#define U5    48
#define S5    16
#define U6    208
#define S6    16
#define U7    368
#define S7    16
#define U8    528
#define S8    16




ZStaticSpotLight::ZStaticSpotLight(const glm::vec3 &Position, const glm::vec3 &LightColor, uint8_t _ZONE)
:TLuz(LightColor), position(Position), ZONE(_ZONE), ACTIVE(false)
{

}

ZStaticSpotLight::ZStaticSpotLight(const ZStaticSpotLight &orig) {
    Color = orig.Color;
    intensidad = orig.intensidad;
    light_shader = orig.light_shader;
    N = orig.N;
    position = orig.position;
    direccion = orig.direccion;
    ZONE = orig.ZONE;
    ACTIVE = orig.ACTIVE;
}


ZStaticSpotLight::~ZStaticSpotLight(){

}

void ZStaticSpotLight::setDireccion(const glm::vec3& dir){
    direccion = dir;
}

void ZStaticSpotLight::beginDraw(){
    //std::cout << "Luz Dirigida" << '\n';
    int offsetpos =        U5 + S5 * N;
    int offsetdir =        U6 + S6 * N;
    int offsetcolor =      U7 + S7 * N;
    int offsetintensidad = U8 + S8 * N;

    glm::vec4 pos = viewMatrix * glm::vec4(position.x, position.y, position.z, 1.0f);
    glm::vec4 dir = viewMatrix * glm::vec4(direccion.x, direccion.y, direccion.z, 1.0f);

    ((float*)(buffer + offsetpos))[0] = pos[0];
    ((float*)(buffer + offsetpos))[1] = pos[1];
    ((float*)(buffer + offsetpos))[2] = pos[2];

    ((float*)(buffer + offsetdir))[0] = dir[0];
    ((float*)(buffer + offsetdir))[1] = dir[1];
    ((float*)(buffer + offsetdir))[2] = dir[2];

    ((float*)(buffer + offsetcolor))[0] = Color.x;
    ((float*)(buffer + offsetcolor))[1] = Color.y;
    ((float*)(buffer + offsetcolor))[2] = Color.z;

    *((float *)(buffer + offsetintensidad)) = intensidad;
}

void ZStaticSpotLight::endDraw(){}
