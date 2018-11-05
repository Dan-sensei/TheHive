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
void Camera::setPosition(const gg::Vector3f &newPosition){
    mCamera->setPosition(
        irr::core::vector3df(newPosition.X, newPosition.Y, newPosition.Z)
    );
}


//  ---
//  Returns the position of the camera
//==================================================================================
gg::Vector3f Camera::getPosition(){
    gg::Vector3f currentPositionGG;
    irr::core::vector3df currentPositionIRR = mCamera->getPosition();

    // Convert the Irrlicht vector to GG vector
    currentPositionGG.X = currentPositionIRR.X;
    currentPositionGG.Y = currentPositionIRR.Y;
    currentPositionGG.Z = currentPositionIRR.Z;

    return currentPositionGG;
}


//  ---
//  Sets where the camera should be looking at
//==================================================================================
void Camera::setTarget(const gg::Vector3f &target){
    mCamera->setTarget(irr::core::vector3df(target.X, target.Y, target.Z));
}
