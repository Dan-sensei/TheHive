#include "Model.hpp"

Model::Model()
:mModel(nullptr)
{

}

Model::Model(const Model &orig){
    mModel = orig.mModel;
}

Model::~Model(){
    mModel->remove();
}

//  ---
//  Sets the camera position
//==================================================================================
void Model::setPosition(const glm::vec3 &newPosition){
    mModel->setPosition(
        irr::core::vector3df(newPosition.x, newPosition.y, newPosition.z)
    );
}

void Model::setRotation(const glm::vec3 &newRotation){
    mModel->setRotation(
        irr::core::vector3df(newRotation.x, newRotation.y, newRotation.z)
    );
}


//  ---
//  Returns the position of the camera
//==================================================================================
glm::vec3 Model::getPosition(){
    glm::vec3 currentPositionGG;
    irr::core::vector3df currentPositionIRR = mModel->getPosition();

    // Convert the Irrlicht vector to GG vector
    currentPositionGG.x = currentPositionIRR.X;
    currentPositionGG.y = currentPositionIRR.Y;
    currentPositionGG.z = currentPositionIRR.Z;

    return currentPositionGG;
}

glm::vec3 Model::getRotation(){
    glm::vec3 currentRotationGG;
    irr::core::vector3df currentRotationIRR = mModel->getRotation();

    // Convert the Irrlicht vector to GG vector
    currentRotationGG.x = currentRotationIRR.X;
    currentRotationGG.y = currentRotationIRR.Y;
    currentRotationGG.z = currentRotationIRR.Z;

    return currentRotationGG;
}

glm::vec3 Model::getScale(){
    glm::vec3 currentScaleGG;
    irr::core::vector3df currentScaleIRR = mModel->getScale();

    // Convert the Irrlicht vector to GG vector
    currentScaleGG.x = currentScaleIRR.X;
    currentScaleGG.y = currentScaleIRR.Y;
    currentScaleGG.z = currentScaleIRR.Z;

    return currentScaleGG;
}

//  ---
//  We assign the material to the model
//==================================================================================
void Model::assignMaterial(const Material &mat) {
    irr::video::ITexture * texture = mat.mMaterial.getTexture(0);
    if(texture)
        mModel->setMaterialTexture(0, texture);
}
