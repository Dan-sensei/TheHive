#include "TLuzPuntual.hpp"
#include <iostream>

TLuzPuntual::TLuzPuntual(){}
TLuzPuntual::~TLuzPuntual(){}

TLuzPuntual::TLuzPuntual(gg::Color &_color,glm::vec3& pos)
:TLuz(_color){
    posicion = pos;
}
void TLuzPuntual::setPosicion(glm::vec3& dir ){
    posicion= dir;
}

glm::vec3 TLuzPuntual::getPosicion(){
    return posicion;
}


// Se quedan vacios
void TLuzPuntual::beginDraw(const uint8_t &T_ID){
    std::cout << "Luz Puntual" << '\n';
}
void TLuzPuntual::endDraw(const uint8_t &T_ID){}
