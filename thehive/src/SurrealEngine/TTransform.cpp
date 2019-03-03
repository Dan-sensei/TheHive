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

void TTransform::translate(gg::Vector3f _vec){
    auto input = glm::vec3(_vec.X,_vec.Y,_vec.Z);
    matrix = glm::translate(matrix,input);
    datos+=input;
}

void TTransform::rotate(float _angle, gg::Vector3f _axis){
    auto input = glm::vec3(_axis.X,_axis.Y,_axis.Z);
    matrix = glm::rotate(matrix,glm::radians(_angle),input);
    datos+=input*_angle;
}

void TTransform::scale(gg::Vector3f _vec){
    matrix = glm::scale(matrix,glm::vec3(_vec.X,_vec.Y,_vec.Z));
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

void TTransform::beginDraw(const uint8_t &T_ID){
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

void TTransform::setPosition(gg::Vector3f _vec){
    identity();
    datos=glm::vec3(0,0,0);
    translate( _vec);
}
void TTransform::setRotation(gg::Vector3f _vec){
    identity();
    datos=glm::vec3(0,0,0);
    rotate(_vec.X, gg::Vector3f(1,0,0));
    rotate(_vec.Y, gg::Vector3f(0,1,0));
    rotate(_vec.Z, gg::Vector3f(0,0,1));
}

void TTransform::endDraw(const uint8_t &T_ID){
    // Desapilar matriz y ponerla como la actual
    modelMatrix = matrixStack.top();
    matrixStack.pop();
}
