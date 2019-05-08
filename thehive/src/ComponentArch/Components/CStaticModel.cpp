#include "CStaticModel.hpp"

CStaticModel::CStaticModel(StandardNode* FATHER, const std::string &pathToModel, ZMaterial* material, const glm::vec3 &Position, const glm::quat &Rotation){
    Surreal = Singleton<Omicron>::Instance();
    _3DModel = Surreal->createStaticMesh(FATHER, pathToModel.c_str(), Position, Rotation);
    Surreal->bindMaterialToMesh(_3DModel, material);
}
CStaticModel::CStaticModel(ZNode* NODE, ZMaterial* material)
:_3DModel(NODE)
{
    Surreal = Singleton<Omicron>::Instance();
    Surreal->bindMaterialToMesh(_3DModel, material);
}

CStaticModel::~CStaticModel(){
    StandardNode *FATHER = static_cast<StandardNode*>(_3DModel->getPadre());
    FATHER->remHijo(_3DModel);
}

void CStaticModel::setVisibility(bool flag){
    _3DModel->setVisibility(flag);
}

void CStaticModel::addLOD(std::string LOD){
    static_cast<ZStaticMesh*>(static_cast<StandardNode*>(_3DModel)->getEntidad())->addLOD(LOD);
}

void CStaticModel::setPosition(const glm::vec3 &Position){
    Surreal->setPosition(_3DModel,Position);
}
