#include "TLuz.hpp"
#include <iostream>

TLuz::TLuz(){}
TLuz::~TLuz(){}

TLuz::TLuz(gg::Color &_color){
    intensidad = _color;
}

void TLuz::setIntensidad(gg::Color &_color){
    intensidad = _color;
}

gg::Color TLuz::getIntensidad(){
    return intensidad;
}

// Se quedan vacios
void TLuz::beginDraw(){
    std::cout << "Luz" << '\n';
}
void TLuz::endDraw(){}
