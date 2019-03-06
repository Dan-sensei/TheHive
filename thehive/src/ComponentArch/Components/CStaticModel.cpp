#include "CStaticModel.hpp"

CStaticModel::CStaticModel(const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::vec3 &Rotation){
    auto Surreal = Singleton<SurrealEngine>::Instance();
    Surreal->bindMaterialToMesh(Surreal->crearMalla(pathToModel.c_str(), Position, Rotation), material);
}

CStaticModel::~CStaticModel(){

}
