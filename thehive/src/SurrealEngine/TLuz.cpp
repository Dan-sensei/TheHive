#include "TLuz.hpp"
#include <iostream>
#include <cstdint>

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
void TLuz::beginDraw(uint8_t tipo_ent){
    if(tipo_ent==0)
        std::cout << "Luz" << '\n';
        //Meter en array de luces
}
void TLuz::endDraw(){}
