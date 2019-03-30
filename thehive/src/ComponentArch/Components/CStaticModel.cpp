#include "CStaticModel.hpp"

CStaticModel::CStaticModel(const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::vec3 &Rotation, int8_t map_zone, const std::string& BoundingBoxPath){
    Surreal = Singleton<Omicron>::Instance();
    _3DModel = Surreal->crearMalla(pathToModel.c_str(), Position, Rotation, map_zone, BoundingBoxPath);
    Surreal->bindMaterialToMesh(_3DModel, material);
}

CStaticModel::~CStaticModel(){
    Surreal->deleteLeafNode(_3DModel);
}

void CStaticModel::setVisibility(bool flag){
    _3DModel->getPadre()->getPadre()->setVisibility(flag);
}

void CStaticModel::setPosition(const glm::vec3 &Position){
    Surreal->setPosition(_3DModel,Position);
}

void CStaticModel::addLOD(std::string LOD){
    static_cast<ZStaticMesh*>(_3DModel->getEntidad())->addLOD(LOD);
}
