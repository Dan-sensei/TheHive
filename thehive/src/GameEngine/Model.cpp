#include "Model.hpp"

Model::Model()
:mModel(nullptr)
{

}

Model::Model(const Model &orig){
    mModel = orig.mModel;
}

Model::~Model(){

}

//  ---
//  Sets the camera position
//==================================================================================
void Model::setPosition(const gg::Vector3f &newPosition){
    mModel->setPosition(
        irr::core::vector3df(newPosition.X, newPosition.Y, newPosition.Z)
    );
}

void Model::setRotation(const gg::Vector3f &newRotation){
    mModel->setRotation(
        irr::core::vector3df(newRotation.X, newRotation.Y, newRotation.Z)
    );
}


//  ---
//  Returns the position of the camera
//==================================================================================
gg::Vector3f Model::getPosition(){
    gg::Vector3f currentPositionGG;
    irr::core::vector3df currentPositionIRR = mModel->getPosition();

    // Convert the Irrlicht vector to GG vector
    currentPositionGG.X = currentPositionIRR.X;
    currentPositionGG.Y = currentPositionIRR.Y;
    currentPositionGG.Z = currentPositionIRR.Z;

    return currentPositionGG;
}

gg::Vector3f Model::getRotation(){
    gg::Vector3f currentRotationGG;
    irr::core::vector3df currentRotationIRR = mModel->getRotation();

    // Convert the Irrlicht vector to GG vector
    currentRotationGG.X = currentRotationIRR.X;
    currentRotationGG.Y = currentRotationIRR.Y;
    currentRotationGG.Z = currentRotationIRR.Z;

    return currentRotationGG;
}

//  ---
//  We assign the material to the model
//==================================================================================
void Model::assignMaterial(const Material &mat) {
    irr::video::ITexture * texture = mat.mMaterial.getTexture(0);
    if(texture)
        mModel->setMaterialTexture(0, texture);
}
