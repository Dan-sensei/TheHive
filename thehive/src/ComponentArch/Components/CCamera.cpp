#include "CCamera.hpp"
#include <ComponentArch/ObjectManager.hpp>


#define CAMERA_ATENUATION 7
#define HEIGHT 0.7
#define RADIUS 2.5

CCamera::CCamera(bool _b)
:mod(nullptr), Engine(nullptr), Manager(nullptr), cam(nullptr),
daniNoSabeProgramar(_b)
{}


CCamera::~CCamera(){}

void CCamera::initComponent(){
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::CAMERA, gg::M_SETPTRS);
}

void CCamera::Init(){

    Engine = Singleton<GameEngine>::Instance();
    Manager = Singleton<ObjectManager>::Instance();
    cam = Engine->getCamera();

    MHandler_SETPTRS();

    lastHeroPosition = mod->getPosition();
    cameraPositionBeforeLockRotation = Engine->getCamera()->getPosition();
}

gg::EMessageStatus CCamera::processMessage(const Message &m) {

    if(m.mType == gg::M_SETPTRS)    return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}

//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CCamera::MHandler_SETPTRS(){
    mod = static_cast<CTransform*>(Manager->getComponent(gg::TRANSFORM, getEntityID()));
    return gg::ST_TRUE;
}


void CCamera::updateCameraTarget(gg::Vector3f nextPosition, bool heroRotation) {
    lastHeroPosition = nextPosition;

    cam->bindTargetAndRotation(true);

    // First of all, we have to get the mouse position on the screen
    // and get the X,Y position
    int screenW = static_cast<int>(Engine->getScreenWidth())/2;
    int screenH = static_cast<int>(Engine->getScreenHeight())/2;

    // Set the coordinates to an absolute 0 on the center of the screen
    // Set the mouse new coordinate to the center(0,0)
    int vX = Engine->getCursorX() - screenW;
    int vY = Engine->getCursorY() - screenH;
    if(daniNoSabeProgramar)
        vY = -vY;
    Engine->setCursorPosition(screenW,screenH);

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

    // We dont set the body position NOW
    // In the CPlayerController Manager we applied the force/impulse to the body

    /////////////////////////////////////////////////////////////////
    // VERTICAL AXIS
    /////////////////////////////////////////////////////////////////
    // Now it's time to set the rotation on the VERTICAL AXIS
    gg::Vector3f finalCameraPosition = cam->getPosition();

    dist = RADIUS;
    angle = -newRotation.X*CAMERA_ATENUATION/400;
    float newY = dist * sin(angle);
    newZ = dist * cos(angle);

    // gg::cout("sin(angle) = "+std::to_string(sin(angle)));
    // gg::cout("cos(angle) = "+std::to_string(cos(angle)));

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

    // Perpendicular vector so set an offset to the right
    gg::Vector3f ppV(
        nextPosition.Z-camPosition.Z,
        0,
        -(nextPosition.X-camPosition.X)
    );
    ppV = gg::Normalice(ppV);

    camPosition = cam->getPosition();
    cam->setPosition(
        gg::Vector3f(
            camPosition.X+ppV.X,
            camPosition.Y,
            camPosition.Z+ppV.Z
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
        // static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY, getEntityID()))->applyTorque(gg::Vector3f(1000,newRotation.Y,0));
        // mod->setRotation(gg::Vector3f(0,newRotation.Y,0));
    }

}

gg::Vector3f CCamera::getCameraPosition(){
    GameEngine *Engine = Singleton<GameEngine>::Instance();
    return Engine->getCamera()->getPosition();
}

gg::Vector3f CCamera::getCameraRotation(){
    GameEngine *Engine = Singleton<GameEngine>::Instance();
    return Engine->getCamera()->getRotation();
}

gg::Vector3f CCamera::getCameraTarget(){
    GameEngine *Engine = Singleton<GameEngine>::Instance();
    return Engine->getCamera()->getTarget();
}

gg::Vector3f CCamera::getlastHeroPosition(){
    return lastHeroPosition;
}

gg::Vector3f CCamera::getCameraPositionBeforeLockRotation(){
    return cameraPositionBeforeLockRotation;
}

void CCamera::setCameraPositionBeforeLockRotation(gg::Vector3f vector){
    cameraPositionBeforeLockRotation = vector;
}
