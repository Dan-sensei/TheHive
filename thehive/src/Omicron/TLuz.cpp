#include "TLuz.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ShaderUniformMapping.hpp>
#include <glm/glm.hpp>
#include <string>

unsigned char * TLuz::buffer=nullptr;
//TLuz::buffer=nullptr;
TLuz::TLuz():light_shader(nullptr),color(0,0,0){}
TLuz::~TLuz(){}

TLuz::TLuz(gg::Color &_color){//,unsigned char * buff):light_shader(nullptr){
    //buffer=buff;
    color = _color;
}

TLuz::TLuz(gg::Color &_color,Shader *_shader){
    color = _color;
    light_shader = _shader;
}

TLuz::TLuz(Shader *_shader){
    color = gg::Color();
    light_shader = _shader;
}

void TLuz::setIntensidad(float &_color){
    intensidad=_color;
}
float TLuz::getIntensidad(){
    return intensidad;
}
void TLuz::setColor(gg::Color &_color){
    color = _color;
}

gg::Color TLuz::getColor(){
    return color;
}

// Se quedan vacios
void TLuz::beginDraw(){
    // Mandar como uniform
    if(light_shader){
        glm::vec4 pos = viewMatrix * modelMatrix[3];

        glUniform3f(_U_LIGHT_POS, pos.x,pos.y,pos.z);
    }
}
void TLuz::endDraw(){}
