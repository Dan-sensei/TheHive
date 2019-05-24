#include "ZStaticPointLight.hpp"

#define U9    688
#define S9    16
#define U10    1008
#define S10    16
#define U11    1328
#define S11    16



ZStaticPointLight::ZStaticPointLight(const glm::vec3 &Position, const glm::vec3 &LightColor, uint8_t _ZONE)
:TLuz(LightColor), position(Position), ZONE(_ZONE), ACTIVE(false)
{}

ZStaticPointLight::ZStaticPointLight(const ZStaticPointLight &orig){
    Color = orig.Color;
    intensidad = orig.intensidad;
    light_shader = orig.light_shader;
    N = orig.N;
    position = orig.position;
    ZONE = orig.ZONE;
    ACTIVE = orig.ACTIVE;
}

ZStaticPointLight::~ZStaticPointLight(){

}



void ZStaticPointLight::beginDraw(){
    //std::cout << "Luz Puntual" << '\n';

    //unsigned int offsetpos = uniformOffsets[9] +arrayStrides[9]*n;
    //unsigned int offsetcolor = uniformOffsets[10] +arrayStrides[10]*n;
    //unsigned int offsetintensidad = uniformOffsets[11] +arrayStrides[11]*n;


    int offsetpos =        U9  + S9  * N;
    int offsetcolor =      U10 + S10 * N;
    int offsetintensidad = U11 + S11 * N;

    glm::vec4 pos = viewMatrix * glm::vec4(position.x, position.y, position.z, 1.0f);


    ((float*)(buffer + offsetpos))[0] = pos[0];
    ((float*)(buffer + offsetpos))[1] = pos[1];
    ((float*)(buffer + offsetpos))[2] = pos[2];


    ((float*)(buffer + offsetcolor))[0] = Color.x;
    ((float*)(buffer + offsetcolor))[1] = Color.y;
    ((float*)(buffer + offsetcolor))[2] = Color.z;

    *((float *)(buffer + offsetintensidad)) = intensidad;

}

void ZStaticPointLight::endDraw(){}
