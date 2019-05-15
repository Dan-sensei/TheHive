#include "TLuzPuntual.hpp"
//#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ShaderUniformMapping.hpp>
#include <glm/glm.hpp>
#include <string>

#define U9    560
#define U10    688
#define U11    816

#define S9    16
#define S10    16
#define S11    16

TLuzPuntual::TLuzPuntual(){}
TLuzPuntual::~TLuzPuntual(){}

TLuzPuntual::TLuzPuntual(gg::Color &_color,glm::vec3& pos)
:TLuz(_color){
    posicion = pos;
}
void TLuzPuntual::setPosicion(glm::vec3& dir ){
    posicion= dir;
}

glm::vec3 TLuzPuntual::getPosicion(){
    return posicion;
}


// Se quedan vacios
void TLuzPuntual::beginDraw(){
    //std::cout << "Luz Puntual" << '\n';

    //unsigned int offsetpos = uniformOffsets[9] +arrayStrides[9]*n;
    //unsigned int offsetcolor = uniformOffsets[10] +arrayStrides[10]*n;
    //unsigned int offsetintensidad = uniformOffsets[11] +arrayStrides[11]*n;


        int offsetpos =        U9 +S9*N;
        int offsetcolor =      U10 +S10*N;
        int offsetintensidad = U11 +S11*N;

        glm::vec4 pos = viewMatrix * modelMatrix[3];

        ((float*)(buffer + offsetpos))[0] = pos[0];
        ((float*)(buffer + offsetpos))[1] = pos[1];
        ((float*)(buffer + offsetpos))[2] = pos[2];


        ((float*)(buffer + offsetcolor))[0] = color.R;
        ((float*)(buffer + offsetcolor))[1] = color.G;
        ((float*)(buffer + offsetcolor))[2] = color.B;

        *((float *)(buffer + offsetintensidad)) = intensidad;

}
void TLuzPuntual::endDraw(){}
