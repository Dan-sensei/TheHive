#include "TLuzDirigida.hpp"
//#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ShaderUniformMapping.hpp>
#include <glm/glm.hpp>
#include <string>

TLuzDirigida::TLuzDirigida(){}
TLuzDirigida::~TLuzDirigida(){}

TLuzDirigida::TLuzDirigida(gg::Color &_color,glm::vec3& dir)
:TLuz(_color){
    direccion = dir;
}
void TLuzDirigida::setDireccion(glm::vec3& dir ){
    direccion= dir;
}

glm::vec3 TLuzDirigida::getDireccion(){
    return direccion;
}


// Se quedan vacios
void TLuzDirigida::beginDraw(){
    //std::cout << "Luz Dirigida" << '\n';

    int n=0;//
    //unsigned int offsetpos = uniformOffsets[5] +arrayStrides[5]*n;
    //unsigned int offsetdir = uniformOffsets[6] +arrayStrides[6]*n;
    //unsigned int offsetcolor = uniformOffsets[7] +arrayStrides[7]*n;
    //unsigned int offsetintensidad = uniformOffsets[8] +arrayStrides[8]*n;
    unsigned int offsetpos          =0;
    unsigned int offsetdir          =0;
    unsigned int offsetcolor        =0;
    unsigned int offsetintensidad   =0;

    //if(light_shader){
        glm::vec4 pos = viewMatrix * modelMatrix[3];

        ((float*)(buffer + offsetpos))[0] = pos[0];
        ((float*)(buffer + offsetpos))[1] = pos[1];
        ((float*)(buffer + offsetpos))[2] = pos[2];

        ((float*)(buffer + offsetdir))[0] = direccion[0];
        ((float*)(buffer + offsetdir))[1] = direccion[1];
        ((float*)(buffer + offsetdir))[2] = direccion[2];

        ((float*)(buffer + offsetcolor))[0] = color.R;
        ((float*)(buffer + offsetcolor))[1] = color.G;
        ((float*)(buffer + offsetcolor))[2] = color.B;

        *((float *)(buffer + offsetintensidad)) = intensidad;


        glUniform3f(_U_LIGHT_POS, pos.x,pos.y,pos.z);
    //}
}
void TLuzDirigida::endDraw(){}
