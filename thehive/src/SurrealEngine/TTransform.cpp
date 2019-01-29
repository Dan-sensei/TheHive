#include "TTransform.hpp"

TTransform::TTransform(){}
TTransform::~TTransform (){}

TTransform::TTransform(glm::mat4 _m){
    matrix = _m;
}

void TTransform::load(glm::mat4 _m){
    matrix = _m;
}

void TTransform::translate(gg::Vector3f _vec){
    matrix = glm::translate(matrix,glm::vec3(_vec.X,_vec.Y,_vec.Z));
}

void TTransform::rotate(float _angle, gg::Vector3f _vec){
    matrix = glm::rotate(matrix,_angle,glm::vec3(_vec.X,_vec.Y,_vec.Z));
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

void TTransform::beginDraw(){

}

void TTransform::endDraw(){

}
