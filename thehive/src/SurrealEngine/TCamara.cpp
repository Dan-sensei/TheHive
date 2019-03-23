#include "TCamara.hpp"
//#include <iostream>
#include <cstdint>



TCamara::TCamara(float _fov, float _near, float _far)
:target(0,0,0), hasTarget(false){
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

void TCamara::setTarget(glm::vec3 &t_pos){
    hasTarget   = true;
    target      = t_pos;
}

void TCamara::beginDraw(){
    // Matriz VISTA
    // -------------------
    // Mirar la funcion Dios glm::decompose si la posicion de la camara no funciona

    if(hasTarget){
        position = modelMatrix[3];
        viewMatrix = glm::lookAt(
            glm::vec3(position),
            target,
            glm::vec3(0,1,0)
        );
    }
    else{
        viewMatrix = glm::inverse(modelMatrix);
    }

}

void TCamara::endDraw(){}

// glm::mat4 GetViewMatrix( ){
//         return glm::lookAt( this->position, this->position + this->front, this->up );
// }
