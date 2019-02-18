#include "TTransform.hpp"

// Pila de matrices
std::stack<glm::mat4> TEntidad::matrixStack;
glm::mat4 TEntidad::modelMatrix;

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

void TTransform::translate(gg::Vector3f _vec){
    matrix = glm::translate(matrix,glm::vec3(_vec.X,_vec.Y,_vec.Z));
}

void TTransform::rotate(float _angle, gg::Vector3f _axis){
    matrix = glm::rotate(matrix,_angle,glm::vec3(_axis.X,_axis.Y,_axis.Z));
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

void TTransform::beginDraw(uint8_t tipo_ent){
    // Apilar matriz y aplicar transformacion a la matriz actual
    // Las grandiosas funciones lambda
    auto resto = [this](){
        modelMatrix = modelMatrix*matrix;
        matrixStack.push(matrix);
    };

    auto it1 = [this](){
        modelMatrix = matrix;
        matrixStack.push(matrix);
    };

    (matrixStack.empty())? it1() : resto();
}

void TTransform::endDraw(){
    // Desapilar matriz y ponerla como la actual
    modelMatrix = matrixStack.top();
    matrixStack.pop();
}
