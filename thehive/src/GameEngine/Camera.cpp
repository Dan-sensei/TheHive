#include "Camera.hpp"

Camera::Camera()
:mCamera(nullptr)
{

}

Camera::Camera(const Camera &orig) {
    mCamera = orig.mCamera;
}

Camera::~Camera() {

}

//  ---
//  Sets the camera position
//==================================================================================
void Camera::setPosition(const glm::vec3 &newPosition){
    mCamera->setPosition(
        irr::core::vector3df(newPosition.x, newPosition.y, newPosition.z)
    );
}

void Camera::setRotation(const glm::vec3 &newRotation){
    mCamera->setRotation(
        irr::core::vector3df(newRotation.x, newRotation.y, newRotation.z)
    );
}


//  ---
//  Returns the position of the camera
//==================================================================================
glm::vec3 Camera::getPosition(){
    glm::vec3 currentPositionGG;
    irr::core::vector3df currentPositionIRR = mCamera->getPosition();

    // Convert the Irrlicht vector to GG vector
    currentPositionGG.x = currentPositionIRR.X;
    currentPositionGG.y = currentPositionIRR.Y;
    currentPositionGG.z = currentPositionIRR.Z;

    return currentPositionGG;
}

glm::vec3 Camera::getRotation(){
    glm::vec3 currentRotationGG;
    irr::core::vector3df currentRotationIRR = mCamera->getRotation();

    // Convert the Irrlicht vector to GG vector
    currentRotationGG.x = currentRotationIRR.X;
    currentRotationGG.y = currentRotationIRR.Y;
    currentRotationGG.z = currentRotationIRR.Z;

    return currentRotationGG;
}

void Camera::updateAbsolutePosition(){
    mCamera->updateAbsolutePosition();
}

void Camera::bindTargetAndRotation(bool bound){
    mCamera->bindTargetAndRotation(bound);
}

//  ---
//  Sets where the camera should be looking at
//==================================================================================
void Camera::setTarget(const glm::vec3 &target){
    mCamera->setTarget(irr::core::vector3df(target.x, target.y, target.z));
}

glm::vec3 Camera::getTarget(){
    return glm::vec3(
        mCamera->getTarget().X,
        mCamera->getTarget().Y,
        mCamera->getTarget().Z);
}
