#include "TCamara.hpp"
#include <iostream>
#include <cstdint>



std::stack<glm::mat4> glMatrixStack;

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
    glm::mat4 ProjMatrix = glm::perspective(
        glm::radians(fov),
        _aspect,
        cercano,
        lejano
    );

    // Se necesita llevar las matrices a variables
    // uniform para el calculo en glsl? -> SE

    // GLuint PerspectiveMatrixID = glGetUniformLocation(cacadevaca,"PPM");
    // glUniformMatrix4fv(PerspectiveMatrixID,1,GL_FALSE,&projection[0][0]);
}
// Se quedan vacios??
void TCamara::beginDraw(uint8_t tipo_ent){
    if(tipo_ent==1)
        std::cout << "Camara" << '\n';
    // Matriz VISTA
    // -------------------
    // Mirar la funcion Dios glm::decompose si la posicion de la camara no funciona

    glm::mat4 view = glm::lookAt(
        glm::vec3(glMatrixStack.top()[3]),  // CameraPosition   -> Cambia con los eventos de teclado
        target,                             // CameraTarget     -> Cambia con los eventos de teclado
        glm::vec3(0,1,0)                    // UpVector
    );
}
void TCamara::endDraw(){}
