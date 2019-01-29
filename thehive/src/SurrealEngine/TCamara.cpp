#include "TCamara.hpp"

TCamara::TCamara(float _fov, float _near, float _far){
    cercano = _near;
    lejano  = _far;
    fov     = _fov;
}

TCamara::~TCamara(){}

void TCamara::changeFov(float _fov){
    fov = _fov;
}

void TCamara::setPerspectiva(float _aspect){
    // Supongo que las transformaciones de
    // la camara se hacen en el beginDraw

    // _aspect = 16/9 | 4/3 | ...
    projection = glm::perspective(
        glm::radians(fov),
        _aspect,
        cercano,
        lejano
    );
}

// Se quedan vacios
void TCamara::beginDraw(){}
void TCamara::endDraw(){}
