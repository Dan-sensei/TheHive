#include "TLuz.hpp"
#include <iostream>

TLuz::TLuz():intensidad(0,0,0),UL(0){}
TLuz::~TLuz(){}

TLuz::TLuz(gg::Color &_color):UL(0){
    intensidad = _color;
}

TLuz::TLuz(gg::Color &_color,Shader *_shader){
    intensidad = _color;
    UL = _shader->getUniformLocation("LightPosition_worldspace");
}

TLuz::TLuz(Shader *_shader){
    intensidad = gg::Color();
    UL = _shader->getUniformLocation("LightPosition_worldspace");
}

void TLuz::setIntensidad(gg::Color &_color){
    intensidad = _color;
}

gg::Color TLuz::getIntensidad(){
    return intensidad;
}


void TLuz::beginDraw(){
    Pos = modelMatrix[3];
    glUniform3f(UL,Pos.x,Pos.y,Pos.z);
    
}

// Se quedan vacios
void TLuz::JustRender(){
    // Mandar como uniform
    glUniform3f(UL,Pos.x,Pos.y,Pos.z);
}
void TLuz::endDraw(){}
