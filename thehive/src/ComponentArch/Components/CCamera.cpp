#include "CCamera.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include <Bullet/ggDynWorld.hpp>

#define PI                  3.1415926535897932384626433832795028841971693993751058209749445923078164062
#define DEGREES_TO_RADIANS  PI/180.f
#define CAMERA_ATENUATION   7.f
#define HEIGHT              0.4
#define RADIUS              2.5

CCamera::CCamera(bool _b)
:Target(nullptr), Engine(nullptr), Manager(nullptr), cam(nullptr),
daniNoSabeProgramar(_b)
{}


CCamera::~CCamera(){
    delete CRigidbody;
}

void CCamera::Init(){
    Engine = Singleton<TMotorTAG>::Instance();
    Manager = Singleton<ObjectManager>::Instance();
    dynWorld = Singleton<ggDynWorld>::Instance();
    cam = Engine->getCamera();

    lastHeroPosition = Target->getPosition();

    cameraPositionBeforeLockRotation = Pos;

    collision = false;
    CRigidbody=new CRigidBody(
        false,
        cameraPositionBeforeLockRotation.X,
        cameraPositionBeforeLockRotation.Y,
        cameraPositionBeforeLockRotation.Z,
        1,1,1
    );


    screenW = Engine->getScreenWidth();
    screenH = Engine->getScreenHeight();
}

void CCamera::setTarget(CTransform *T) {
    Target = T;
}

void CCamera::CameraUpdate(){
    gg::Vector3f nextPosition = Target->getPosition();
    lastHeroPosition = nextPosition;

    //cam->bindTargetAndRotation(true);

    gg::Vector3f camPosition = Pos;
    gg::Vector3f backupRotation = Rot;
    gg::Vector3f newRotation = backupRotation;
    gg::Vector3f finalXRVector;
    gg::Vector3f finalYRVector;
    gg::Vector3f finalCameraPosition;

    /////////////////////////////////////////////////////////////////
    // SET ROTATION
    /////////////////////////////////////////////////////////////////
    getNewRotation(newRotation);

    /////////////////////////////////////////////////////////////////
    // HORIZONTAL AXIS
    /////////////////////////////////////////////////////////////////
    setHorizontalAxis(nextPosition,finalXRVector,newRotation,finalCameraPosition);

    /////////////////////////////////////////////////////////////////
    // VERTICAL AXIS
    /////////////////////////////////////////////////////////////////
    setVerticalAxis(nextPosition,finalYRVector,newRotation,finalCameraPosition);

    // FIRST we have to set the camera position
    gg::Vector3f auxCamvector(
        finalXRVector.X,
        finalYRVector.Y+HEIGHT,
        finalXRVector.Z
    );
    Pos = camPosition+auxCamvector;
    Engine->setPosition(cam, Pos);

    // Perpendicular vector to set an offset to the right
    setPerpendicularOffsetVector(nextPosition);

    /////////////////////////////////////////////////////////////////
    // CAMERA COLLISIONS
    /////////////////////////////////////////////////////////////////
    fixCameraPositionOnCollision(nextPosition);

    // Call to updateAbsolutePosition() to avoid perspective and camera position problems
    // ¡¡¡¡ THIS MUST BE THE LAST FUNCTION TO CALL AFTER ANY CAMERA POSITION CHANGING FUNCTION !!!!
    // [IRRLICHT FUNCTION]
    //cam->updateAbsolutePosition();

    setFinalRotation(newRotation,backupRotation, true);
}

void CCamera::setHorizontalAxis(gg::Vector3f &nextPosition,gg::Vector3f &finalXRVector,gg::Vector3f &newRotation,gg::Vector3f &ret_position){
    gg::Vector3f cam_position = Pos;
    float angle,newX,newZ;

    angle   = newRotation.Y*DEGREES_TO_RADIANS;
    newX    = RADIUS * sin(angle);
    newZ    = RADIUS * cos(angle);

    cam_position.X += newX;
    cam_position.Z += newZ;

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    finalXRVector = nextPosition-cam_position;
    ret_position = cam_position;
}

void CCamera::setVerticalAxis(gg::Vector3f &nextPosition,gg::Vector3f &finalYRVector,gg::Vector3f &newRotation, gg::Vector3f &finalCameraPosition){
    float angle,newY,newZ;

    angle = -newRotation.X*DEGREES_TO_RADIANS;
    newY = RADIUS * sin(angle);
    newZ = RADIUS * cos(angle);

    finalCameraPosition.Y += newY;
    finalCameraPosition.X += newZ;

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    finalYRVector = nextPosition-finalCameraPosition;
}

void CCamera::setPerpendicularOffsetVector(gg::Vector3f &nextPosition){
    // Update camera position
    gg::Vector3f camPosition = Pos;
    gg::Vector3f ppV(
        nextPosition.Z-camPosition.Z,
        0,
        -(nextPosition.X-camPosition.X)
    );
    ppV = gg::Normalice(ppV);
    offsetPositionVector = ppV;

    moveCameraPosition(ppV);
}

void CCamera::getNewRotation(gg::Vector3f &newRotation){
    double vX,vY;
    // Set the coordinates to an absolute 0 on the center of the screen
    // Set the mouse new coordinate to the center(0,0)
    Engine->getCursorPosition(vX,vY);
    vX -= screenW;
    vY -= screenH;

    if(daniNoSabeProgramar)
        vY = -vY;

    // ------------------------------------------ //
    // NO SE QUE ES MAS OPTIMO :lenny_face:
    newRotation += (gg::Vector3f(vY,vX,0))/CAMERA_ATENUATION;
    // ------------------------------------------ //
    // newRotation.X += vY/CAMERA_ATENUATION;
    // newRotation.Y += vX/CAMERA_ATENUATION;
    // newRotation.Z  = 0;
    // ------------------------------------------ //
}

void CCamera::setFinalRotation(gg::Vector3f &newRotation,gg::Vector3f &backupRotation,bool heroRotation){
    // SECOND set the camera rotation
    if(newRotation.X > -60 && newRotation.X <= 60){
        Engine->setRotation(cam, heroRotation);
        Rot = newRotation;

    }
    else{
        Engine->setRotation(cam, backupRotation);
        Rot = backupRotation;
    }

    // If heroRotation is FALSE, the hero won't move with the camera rotation
    //if(heroRotation){
        cameraPositionBeforeLockRotation = Pos;
        // mod->setRotation(gg::Vector3f(0,newRotation.Y,0));
    //}
}

void CCamera::fixCameraPositionOnCollision(gg::Vector3f &nextPosition){
    gg::Vector3f camPosition = Pos;
    // Las dos mejores lineas que he escrito en mi vida
    gg::Vector3f FIXED_NEXT_POSITION = nextPosition+(camPosition-nextPosition)*0.2;
    if(dynWorld->RayCastTest(FIXED_NEXT_POSITION,camPosition,pos_on_collision)){
        Engine->setPosition(cam, pos_on_collision);
        Pos = pos_on_collision;
    }
}

gg::Vector3f CCamera::getOffsetPositionVector(){
    return offsetPositionVector;
}

gg::Vector3f CCamera::getCameraPosition(){
    return Pos;
}

gg::Vector3f CCamera::getCameraRotation(){
    return Rot;
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

void CCamera::moveCameraPosition(gg::Vector3f _offPos){
    Pos += _offPos;
    Engine->setPosition(cam, Pos);
}
