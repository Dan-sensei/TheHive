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

    // Matriz PROYECCION
    // _aspect = 16/9 | 4/3 | ...
    projection = glm::perspective(
        glm::radians(fov),
        _aspect,
        cercano,
        lejano
    );

    // Matriz VISTA
    // TODO: Matriz vista

    // Se necesita llevar las matrices a variables
    // uniform para el calculo en glsl? -> PUEDE SER QUE SI

    // GLuint PerspectiveMatrixID = glGetUniformLocation(cacadevaca,"PPM");
    // glUniformMatrix4fv(PerspectiveMatrixID,1,GL_FALSE,&projection[0][0]);
}

// Se quedan vacios
void TCamara::beginDraw(){}
void TCamara::endDraw(){}
