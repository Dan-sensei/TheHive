#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/InitStructs.hpp>

#define CAMERA_ATENUATION 7

CCamera::CCamera(){
    GameEngine *engine = Singleton<GameEngine>::Instance();
    lastCameraPosition = engine->getCamera()->getPosition();
}
CCamera::~CCamera(){}

void CCamera::initComponent(){
    // Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::CAMERA, gg::M_UPDATE);
}

// void CCamera::updateCameraTarget(Camera *cam, Model *mod, gg::Vector3f nextPosition){
void CCamera::updateCameraTarget(uint16_t entity,gg::Vector3f nextPosition){
    if(lastCameraPosition.X!=nextPosition.X && lastCameraPosition.Y!=nextPosition.Y && lastCameraPosition.Z!=nextPosition.Z){
        return;
    }
    lastCameraPosition = nextPosition;

    GameEngine *engine = Singleton<GameEngine>::Instance();
    ObjectManager *manager = Singleton<ObjectManager>::Instance();
    Camera *cam = engine->getCamera();
    CTransform *mod = dynamic_cast<CTransform*>(manager->getComponent(gg::TRANSFORM,entity));

    cam->bindTargetAndRotation(true);
    std::cout << nextPosition.X << "," << nextPosition.Y << "," << nextPosition.Z << '\n';

    // // First of all, we have to get the mouse position on the screen
    // // and get the X,Y position
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

    // // FIRST the camera must be moved
    gg::Vector3f nextCamPosition;
    nextCamPosition.X = nextPosition.X;
    nextCamPosition.Y = nextPosition.Y+10.f;
    nextCamPosition.Z = nextPosition.Z-12.f;
    cam->setPosition(nextCamPosition);
    //
    // // Call to updateAbsolutePosition() to avoid perspective
    // // and camera position problems
    cam->updateAbsolutePosition();

    // SECOND set the camera rotation
    gg::Vector3f newRotation = cam->getRotation();
    newRotation.X += newVY/CAMERA_ATENUATION;
    newRotation.Y += newVX/CAMERA_ATENUATION;
    newRotation.Z = 0;
    cam->setRotation(newRotation);

    // Now is applied the rotation
    // Having the rotation center on the camera position
    gg::Vector3f nextModelPosition = cam->getPosition();
    nextModelPosition.Y -= 10;

    float dist = 12;
    float angle = newRotation.Y*CAMERA_ATENUATION/400;
    float newX = dist * sin(angle);
    float newZ = dist * cos(angle);

    nextModelPosition.X += newX;
    nextModelPosition.Z += newZ;

    // mod->setRotation(gg::Vector3f(0,newRotation.Y,0));
    mod->setPosition(gg::Vector3f(nextModelPosition));

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    gg::Vector3f finalVector;
    finalVector.X = nextPosition.X-mod->getPosition().X;
    finalVector.Y = nextPosition.Y-mod->getPosition().Y;
    finalVector.Z = nextPosition.Z-mod->getPosition().Z;

    mod->setPosition(gg::Vector3f(
        mod->getPosition().X+finalVector.X,
        mod->getPosition().Y+finalVector.Y,
        mod->getPosition().Z+finalVector.Z));

    cam->setPosition(gg::Vector3f(
        cam->getPosition().X+finalVector.X,
        cam->getPosition().Y+finalVector.Y,
        cam->getPosition().Z+finalVector.Z));
    cam->updateAbsolutePosition();
    cam->setRotation(newRotation);

}

gg::Vector3f CCamera::getCameraPosition(){
    GameEngine *engine = Singleton<GameEngine>::Instance();
    return engine->getCamera()->getPosition();
}

gg::Vector3f CCamera::getLastCameraPosition(){
    return lastCameraPosition;
}










