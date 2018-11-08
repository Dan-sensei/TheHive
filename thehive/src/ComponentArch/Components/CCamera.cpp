#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/InitStructs.hpp>

#define CAMERA_ATENUATION 7
#define HEIGHT 10
#define RADIUS 12

CCamera::CCamera(){
}


CCamera::~CCamera(){}

void CCamera::initComponent(){
    // Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::CAMERA, gg::M_UPDATE);
}

void CCamera::initializeComponentData(const void* data){}

/*      Init     */
void CCamera::initAfterComponentAssigment() {
    std::cout << "Init CCamera" << '\n';
    GameEngine *engine = Singleton<GameEngine>::Instance();
    lastCameraPosition = engine->getCamera()->getPosition();
    cameraPositionBeforeLockRotation = lastCameraPosition;

}


// void CCamera::updateCameraTarget(Camera *cam, Model *mod, gg::Vector3f nextPosition){
void CCamera::updateCameraTarget(uint16_t entity,gg::Vector3f nextPosition, bool heroRotation){
    lastCameraPosition = nextPosition;

    GameEngine *engine = Singleton<GameEngine>::Instance();
    ObjectManager *manager = Singleton<ObjectManager>::Instance();
    Camera *cam = engine->getCamera();
    CTransform *mod = dynamic_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,entity));

    cam->bindTargetAndRotation(true);

    // First of all, we have to get the mouse position on the screen
    // and get the X,Y position
    int screenW = static_cast<int>(engine->getScreenWidth())/2;
    int screenH = static_cast<int>(engine->getScreenHeight())/2;

    // Set the coordinates to an absolute 0 on the center of the screen
    // Set the mouse new coordinate to the center(0,0)
    int vX = engine->getCursorX() - screenW;
    int vY = engine->getCursorY() - screenH;
    engine->setCursorPosition(screenW,screenH);

    // And cast it to a float value
    float newVY = static_cast<float>(vY);
    float newVX = static_cast<float>(vX);

    gg::Vector3f backupRotation = cam->getRotation();
    gg::Vector3f newRotation = cam->getRotation();
    newRotation.X += newVY/CAMERA_ATENUATION;
    newRotation.Y += newVX/CAMERA_ATENUATION;
    newRotation.Z = 0;

    /////////////////////////////////////////////////////////////////
    // HORIZONTAL AXIS
    /////////////////////////////////////////////////////////////////
    // Now is applied the rotation on the HORIZONTAL AXIS
    // Having the rotation center on the camera position
    gg::Vector3f nextModelPosition = cam->getPosition();
    nextModelPosition.Y -= HEIGHT;

    float dist = RADIUS;
    float angle = newRotation.Y*CAMERA_ATENUATION/400;
    float newX = dist * sin(angle);
    float newZ = dist * cos(angle);

    nextModelPosition.X += newX;
    nextModelPosition.Z += newZ;

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    gg::Vector3f finalXRVector(
        nextPosition.X-nextModelPosition.X,
        nextPosition.Y-nextModelPosition.Y,
        nextPosition.Z-nextModelPosition.Z
    );

    // And set the entity position
    mod->setPosition(
        gg::Vector3f(
            nextModelPosition.X+finalXRVector.X,
            nextModelPosition.Y+finalXRVector.Y,
            nextModelPosition.Z+finalXRVector.Z
        )
    );

    /////////////////////////////////////////////////////////////////
    // VERTICAL AXIS
    /////////////////////////////////////////////////////////////////
    // Now it's time to set the rotation on the VERTICAL AXIS
    gg::Vector3f finalCameraPosition = cam->getPosition();

    dist = RADIUS+2;
    angle = -newRotation.X*CAMERA_ATENUATION/400;
    float newY = dist * sin(angle);
    newZ = dist * cos(angle);

    finalCameraPosition.Y += newY;
    finalCameraPosition.Z += newZ;

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    gg::Vector3f finalYRVector(
        nextPosition.X-finalCameraPosition.X,
        nextPosition.Y-finalCameraPosition.Y,
        nextPosition.Z-finalCameraPosition.Z
    );

    // FIRST we have to set the camera position
    gg::Vector3f camPosition = cam->getPosition();
    cam->setPosition(
        gg::Vector3f(
            camPosition.X+finalXRVector.X,
            camPosition.Y+finalYRVector.Y+HEIGHT,
            camPosition.Z+finalXRVector.Z
        )
    );



    // Call to updateAbsolutePosition() to avoid perspective
    // and camera position problems
    cam->updateAbsolutePosition();

    // SECOND set the camera rotation
    if(newRotation.X >= -30 && newRotation.X <= 60)
        cam->setRotation(newRotation);
    else
        cam->setRotation(backupRotation);

    // If heroRotation is FALSE, the hero won't move with the camera rotation
    if(heroRotation){
        cameraPositionBeforeLockRotation = cam->getPosition();
        mod->setRotation(gg::Vector3f(0,newRotation.Y,0));
    }

}

gg::Vector3f CCamera::getCameraPosition(){
    GameEngine *engine = Singleton<GameEngine>::Instance();
    return engine->getCamera()->getPosition();
}

gg::Vector3f CCamera::getCameraTarget(){
    GameEngine *engine = Singleton<GameEngine>::Instance();
    return engine->getCamera()->getTarget();
}

gg::Vector3f CCamera::getLastCameraPosition(){
    return lastCameraPosition;
}

gg::Vector3f CCamera::getCameraPositionBeforeLockRotation(){
    return cameraPositionBeforeLockRotation;
}

void CCamera::setCameraPositionBeforeLockRotation(gg::Vector3f vector){
    cameraPositionBeforeLockRotation = vector;
}








