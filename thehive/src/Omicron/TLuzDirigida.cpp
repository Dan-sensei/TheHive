#include "TLuzDirigida.hpp"
//#include <iostream>

TLuzDirigida::TLuzDirigida(){}
TLuzDirigida::~TLuzDirigida(){}

TLuzDirigida::TLuzDirigida(gg::Color &_color,glm::vec3& dir)
:TLuz(_color){
    direccion = dir;
}
void TLuzDirigida::setDireccion(glm::vec3& dir ){
    direccion= dir;
}

glm::vec3 TLuzDirigida::getDireccion(){
    return direccion;
}


// Se quedan vacios
void TLuzDirigida::beginDraw(){
    //std::cout << "Luz Dirigida" << '\n';
}
void TLuzDirigida::endDraw(){}
