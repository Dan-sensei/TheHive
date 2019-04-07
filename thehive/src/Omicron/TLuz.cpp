#include "TLuz.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <iostream>
#include <ShaderUniformMapping.hpp>


TLuz::TLuz():light_shader(nullptr),intensidad(0,0,0){}
TLuz::~TLuz(){}

TLuz::TLuz(gg::Color &_color):light_shader(nullptr){
    intensidad = _color;
}

TLuz::TLuz(gg::Color &_color,Shader *_shader){
    intensidad = _color;
    light_shader = _shader;
}

TLuz::TLuz(Shader *_shader){
    intensidad = gg::Color();
    light_shader = _shader;
}

void TLuz::setIntensidad(gg::Color &_color){
    intensidad = _color;
}

gg::Color TLuz::getIntensidad(){
    return intensidad;
}

// Se quedan vacios
void TLuz::beginDraw(){
    // Mandar como uniform
    if(light_shader){
        glm::vec3 pos = glm::vec3(modelMatrix[3]);
        glUniform3f(_U_LIGHT_POS,pos.x,pos.y,pos.z);
    }
}
void TLuz::endDraw(){}
