#include "TCamara.hpp"
#include <iostream>
#include <cstdint>



TCamara::TCamara(float _fov, float _near, float _far)
:target(0,0,0){
    fov         = _fov;
    cercano     = _near;
    lejano      = _far;
}

TCamara::~TCamara(){}

void TCamara::changeFov(float _fov){
    fov = _fov;
}

void TCamara::setPerspectiva(float _aspect){
    // Matriz PROYECCION
    // -------------------
    // _aspect = 16/9 | 4/3 | ... -> Aspecto de la pantalla
    projMatrix = glm::perspective(
        glm::radians(fov),
        _aspect,
        cercano,
        lejano
    );
}
// Se quedan vacios??
void TCamara::beginDraw(){

    // Matriz VISTA
    // -------------------
    // Mirar la funcion Dios glm::decompose si la posicion de la camara no funciona

    // viewMatrix = glm::lookAt(
    //     // glm::vec3(20,0,0),
    //     glm::vec3(modelMatrix[3]),  // CameraPosition   -> Cambia con los eventos de teclado
    //     target,                             // CameraTarget     -> Cambia con los eventos de teclado
    //     glm::vec3(0,1,0)                    // UpVector
    // );
    viewMatrix = glm::inverse(modelMatrix);
}
void TCamara::endDraw(){}
