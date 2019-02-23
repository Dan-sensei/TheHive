#include "TLuzDirigida.hpp"
#include <iostream>

TLuzDirigida::TLuzDirigida(){}
TLuzDirigida::~TLuzDirigida(){}

TLuzDirigida::TLuzDirigida(gg::Color &_color,gg::Vector3f& dir)
:TLuz(_color){
    direccion = dir;
}
void TLuzDirigida::setDireccion(gg::Vector3f& dir ){
    direccion= dir;
}

gg::Vector3f TLuzDirigida::getDireccion(){
    return direccion;
}


// Se quedan vacios
void TLuzDirigida::beginDraw(const uint8_t &T_ID){
    std::cout << "Luz Dirigida" << '\n';
}
void TLuzDirigida::endDraw(const uint8_t &T_ID){}
