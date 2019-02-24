#include "TLuzPuntual.hpp"
#include <iostream>

TLuzPuntual::TLuzPuntual(){}
TLuzPuntual::~TLuzPuntual(){}

TLuzPuntual::TLuzPuntual(gg::Color &_color,gg::Vector3f& pos)
:TLuz(_color){
    posicion = pos;
}
void TLuzPuntual::setPosicion(gg::Vector3f& dir ){
    posicion= dir;
}

gg::Vector3f TLuzPuntual::getPosicion(){
    return posicion;
}


// Se quedan vacios
void TLuzPuntual::beginDraw(const uint8_t &T_ID){
    std::cout << "Luz Puntual" << '\n';
}
void TLuzPuntual::endDraw(const uint8_t &T_ID){}
