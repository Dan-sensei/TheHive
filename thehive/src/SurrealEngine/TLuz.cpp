#include "TLuz.hpp"
#include <iostream>

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
void TLuz::beginDraw(const uint8_t &T_ID){
    // Mandar como uniform
    if(T_ID == 0){
        if(light_shader){
            GLuint UL = light_shader->getUniformLocation("LightPosition_worldspace");
            glm::vec3 pos = glm::vec3(modelMatrix[3]);
            glUniform3f(UL,pos.x,pos.y,pos.z);
        }
    }
}
void TLuz::endDraw(const uint8_t &T_ID){}
