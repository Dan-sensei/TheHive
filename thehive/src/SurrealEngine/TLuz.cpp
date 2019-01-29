#include "TLuz.hpp"

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
void TLuz::beginDraw(){}
void TLuz::endDraw(){}
