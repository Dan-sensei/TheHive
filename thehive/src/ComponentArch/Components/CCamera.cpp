#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/InitStructs.hpp>

#define CAMERA_ATENUATION 7
#define OFFSET_POSITION_Y 10
#define OFFSET_POSITION_Z 12

CCamera::CCamera(){
    GameEngine *engine = Singleton<GameEngine>::Instance();
    lastCameraPosition = engine->getCamera()->getPosition();
}
CCamera::~CCamera(){}

void CCamera::initComponent(){
    // Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::CAMERA, gg::M_UPDATE);
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

    gg::Vector3f newRotation = cam->getRotation();
    newRotation.X += newVY/CAMERA_ATENUATION;
    newRotation.Y += newVX/CAMERA_ATENUATION;
    newRotation.Z = 0;

    // Now is applied the rotation
    // Having the rotation center on the camera position
    gg::Vector3f nextModelPosition = cam->getPosition();
    nextModelPosition.Y -= OFFSET_POSITION_Y;

    float dist = OFFSET_POSITION_Z;
    float angle = newRotation.Y*CAMERA_ATENUATION/400;
    float newX = dist * sin(angle);
    float newZ = dist * cos(angle);

    nextModelPosition.X += newX;
    nextModelPosition.Z += newZ;

    // If heroRotation is FALSE, the hero won't move with the camera rotation
    if(heroRotation)
        mod->setRotation(gg::Vector3f(0,newRotation.Y,0));
    // mod->setPosition(gg::Vector3f(nextModelPosition));

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    gg::Vector3f finalVector;
    finalVector.X = nextPosition.X-nextModelPosition.X;
    finalVector.Y = nextPosition.Y-nextModelPosition.Y;
    finalVector.Z = nextPosition.Z-nextModelPosition.Z;

    // And set the entity position
    mod->setPosition(
        gg::Vector3f(
            nextModelPosition.X+finalVector.X,
            nextModelPosition.Y+finalVector.Y,
            nextModelPosition.Z+finalVector.Z
        )
    );

    // FIRST we have to set the camera position
    gg::Vector3f camPosition = cam->getPosition();
    cam->setPosition(
        gg::Vector3f(
            camPosition.X+finalVector.X,
            camPosition.Y+finalVector.Y,
            camPosition.Z+finalVector.Z
        )
    );

    // Call to updateAbsolutePosition() to avoid perspective
    // and camera position problems
    cam->updateAbsolutePosition();

    // SECOND set the camera rotation
    cam->setRotation(newRotation);

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










