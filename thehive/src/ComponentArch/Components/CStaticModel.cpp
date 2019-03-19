#include "CStaticModel.hpp"

CStaticModel::CStaticModel(const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::vec3 &Rotation, int8_t map_zone){
    Surreal = Singleton<SurrealEngine>::Instance();
    _3DModel = Surreal->crearMalla(pathToModel.c_str(), Position, Rotation, map_zone);
    Surreal->bindMaterialToMesh(_3DModel, material);
}

CStaticModel::~CStaticModel(){

}

void CStaticModel::setVisibility(bool flag){
    _3DModel->getPadre()->getPadre()->setVisibility(flag);
}

void CStaticModel::setPosition(const glm::vec3 &Position){
    Surreal->setPosition(_3DModel,Position);
}
