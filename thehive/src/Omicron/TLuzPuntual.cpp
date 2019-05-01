#include "TLuzPuntual.hpp"
//#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ShaderUniformMapping.hpp>
#include <glm/glm.hpp>
#include <string>

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

    int n=0;//
    //unsigned int offsetpos = uniformOffsets[9] +arrayStrides[9]*n;
    //unsigned int offsetcolor = uniformOffsets[10] +arrayStrides[10]*n;
    //unsigned int offsetintensidad = uniformOffsets[11] +arrayStrides[11]*n;
    unsigned int offsetpos          =0;
    unsigned int offsetcolor        =0;
    unsigned int offsetintensidad   =0;

    //if(light_shader){
        glm::vec4 pos = viewMatrix * modelMatrix[3];

        ((float*)(buffer + offsetpos))[0] = pos[0];
        ((float*)(buffer + offsetpos))[1] = pos[1];
        ((float*)(buffer + offsetpos))[2] = pos[2];


        ((float*)(buffer + offsetcolor))[0] = color.R;
        ((float*)(buffer + offsetcolor))[1] = color.G;
        ((float*)(buffer + offsetcolor))[2] = color.B;

        *((float *)(buffer + offsetintensidad)) = intensidad;


        glUniform3f(_U_LIGHT_POS, pos.x,pos.y,pos.z);
}
void TLuzPuntual::endDraw(){}
