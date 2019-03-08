#include "CStaticModel.hpp"

CStaticModel::CStaticModel(const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::vec3 &Rotation){
    auto Surreal = Singleton<SurrealEngine>::Instance();
    _3DModel = Surreal->crearMalla(pathToModel.c_str(), Position, Rotation);
    Surreal->bindMaterialToMesh(_3DModel, material);
}

CStaticModel::~CStaticModel(){

}

void CStaticModel::setVisibility(bool flag){
    _3DModel->getPadre()->getPadre()->setVisibility(flag);
}
