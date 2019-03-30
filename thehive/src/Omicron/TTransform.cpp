#include "TTransform.hpp"

// Pila de matrices
// std::stack<glm::mat4> TEntidad::matrixStack;
// glm::mat4 TEntidad::modelMatrix;

TTransform::TTransform(){
    identity();
}

TTransform::~TTransform(){}

TTransform::TTransform(glm::mat4 _m){
    matrix = _m;
}

void TTransform::load(glm::mat4 _m){
    matrix = _m;
}
glm::vec3 TTransform::getDatos(){
    return datos;
}

void TTransform::translate(glm::vec3 _vec){
    matrix = glm::translate(matrix,_vec);
    datos+=_vec;
}

void TTransform::rotate(float _angle, glm::vec3 _axis){
    matrix = glm::rotate(matrix,glm::radians(_angle),_axis);
    datos+=_axis*_angle;
}

void TTransform::scale(glm::vec3 _vec){
    matrix = glm::scale(matrix,_vec);
}

void TTransform::identity(){
    matrix = glm::mat4(1.0f);
}

void TTransform::transpose(){
    matrix = glm::transpose(matrix);
}

void TTransform::inverse(){
    matrix = glm::inverse(matrix);
}

void TTransform::beginDraw(){
    // Apilar matriz y aplicar transformacion a la matriz actual
    // Las grandiosas funciones lambda
    auto resto = [this](){
        modelMatrix = matrix*modelMatrix;
        matrixStack.push(matrix);
    };

    auto it1 = [this](){
        modelMatrix = matrix;
        matrixStack.push(matrix);
    };

    (matrixStack.empty())? it1() : resto();
}

void TTransform::setPosition(glm::vec3 _vec){
    identity();
    datos=glm::vec3(0,0,0);
    translate( _vec);
}

void TTransform::setRotation(glm::vec3 _vec){
    identity();
    datos=glm::vec3(0,0,0);
    rotate(_vec.y, glm::vec3(0,1,0));
    rotate(_vec.x, glm::vec3(1,0,0));
    rotate(_vec.z, glm::vec3(0,0,1));
}

void TTransform::endDraw(){
    // Desapilar matriz y ponerla como la actual
    modelMatrix = matrixStack.top();
    matrixStack.pop();
}
