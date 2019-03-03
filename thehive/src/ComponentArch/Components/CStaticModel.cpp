#include "CStaticModel.hpp"

CStaticModel::CStaticModel(const std::string &pathToModel, ZMaterial* material, const gg::Vector3f &Position, const gg::Vector3f &Rotation){
    auto Surreal = Singleton<TMotorTAG>::Instance();
    Surreal->bindMaterialToMesh(Surreal->crearMalla(pathToModel.c_str(), Position, Rotation), material);
}

CStaticModel::~CStaticModel(){

}
