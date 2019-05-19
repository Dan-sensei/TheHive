#include "TLuz.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ShaderUniformMapping.hpp>
#include <glm/glm.hpp>
#include <string>

unsigned char * TLuz::buffer=nullptr;
//TLuz::buffer=nullptr;
TLuz::TLuz()
:light_shader(nullptr),Color(0,0,0)
{}

TLuz::~TLuz()
{}

TLuz::TLuz(const glm::vec3 &_color){//,unsigned char * buff):light_shader(nullptr){
    //buffer=buff;
    Color = _color;
    N = 0;
}

TLuz::TLuz(const glm::vec3 &_color, Shader *_shader){
    Color = _color;
    light_shader = _shader;
}
void TLuz::setN(int ene){
    N=ene;
}

TLuz::TLuz(Shader *_shader){
    Color = glm::vec3();
    light_shader = _shader;
}

void TLuz::setIntensidad(float &_color){
    intensidad=_color;
}
float TLuz::getIntensidad(){
    return intensidad;
}
void TLuz::setColor(const glm::vec3 &_color){
    Color = _color;
}

glm::vec3 TLuz::getColor(){
    return Color;
}

// // Se quedan vacios
// void TLuz::beginDraw(){
//     // Mandar como uniform
//     if(light_shader){
//         glm::vec4 pos = viewMatrix * modelMatrix[3];
//
//         glUniform3f(_U_LIGHT_POS, pos.x,pos.y,pos.z);
//     }
// }
// void TLuz::endDraw(){}
