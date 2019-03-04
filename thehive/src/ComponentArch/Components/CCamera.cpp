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
        cameraPositionBeforeLockRotation.x,
        cameraPositionBeforeLockRotation.y,
        cameraPositionBeforeLockRotation.z,
        1,1,1
    );


    screenW = Engine->getScreenWidth();
    screenH = Engine->getScreenHeight();
}

void CCamera::setTarget(CTransform *T) {
    Target = T;
}

void CCamera::CameraUpdate(){
    glm::vec3 nextPosition = Target->getPosition();
    lastHeroPosition = nextPosition;

    //cam->bindTargetAndRotation(true);

    glm::vec3 camPosition = Pos;
    glm::vec3 backupRotation = Rot;
    glm::vec3 newRotation = backupRotation;
    glm::vec3 finalXRVector;
    glm::vec3 finalYRVector;
    glm::vec3 finalCameraPosition;

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
    glm::vec3 auxCamvector(
        finalXRVector.x,
        finalYRVector.y+HEIGHT,
        finalXRVector.z
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

void CCamera::setHorizontalAxis(glm::vec3 &nextPosition,glm::vec3 &finalXRVector,glm::vec3 &newRotation,glm::vec3 &ret_position){
    glm::vec3 cam_position = Pos;
    float angle,newX,newZ;

    angle   = newRotation.y*DEGREES_TO_RADIANS;
    newX    = RADIUS * sin(angle);
    newZ    = RADIUS * cos(angle);

    cam_position.x += newX;
    cam_position.z += newZ;

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    finalXRVector = nextPosition-cam_position;
    ret_position = cam_position;
}

void CCamera::setVerticalAxis(glm::vec3 &nextPosition,glm::vec3 &finalYRVector,glm::vec3 &newRotation, glm::vec3 &finalCameraPosition){
    float angle,newY,newZ;

    angle = -newRotation.x*DEGREES_TO_RADIANS;
    newY = RADIUS * sin(angle);
    newZ = RADIUS * cos(angle);

    finalCameraPosition.y += newY;
    finalCameraPosition.x += newZ;

    // Now set the 'OFFSET' to the nextPosition to cheat the player eyes
    finalYRVector = nextPosition-finalCameraPosition;
}

void CCamera::setPerpendicularOffsetVector(glm::vec3 &nextPosition){
    // Update camera position
    glm::vec3 camPosition = Pos;
    glm::vec3 ppV(
        nextPosition.z-camPosition.z,
        0,
        -(nextPosition.x-camPosition.x)
    );
    ppV = glm::normalize(ppV);
    offsetPositionVector = ppV;

    moveCameraPosition(ppV);
}

void CCamera::getNewRotation(glm::vec3 &newRotation){
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
    newRotation += (glm::vec3(vY,vX,0))/CAMERA_ATENUATION;
    // ------------------------------------------ //
    // newRotation.x += vY/CAMERA_ATENUATION;
    // newRotation.y += vX/CAMERA_ATENUATION;
    // newRotation.z  = 0;
    // ------------------------------------------ //
}

void CCamera::setFinalRotation(glm::vec3 &newRotation,glm::vec3 &backupRotation,bool heroRotation){
    // SECOND set the camera rotation
    if(newRotation.x > -60 && newRotation.x <= 60){
        Engine->setRotation(cam, newRotation);
        Rot = newRotation;

    }
    else{
        Engine->setRotation(cam, backupRotation);
        Rot = backupRotation;
    }

    // If heroRotation is FALSE, the hero won't move with the camera rotation
    //if(heroRotation){
        cameraPositionBeforeLockRotation = Pos;
        // mod->setRotation(glm::vec3(0,newRotation.y,0));
    //}
}

void CCamera::fixCameraPositionOnCollision(glm::vec3 &nextPosition){
    glm::vec3 camPosition = Pos;
    // Las dos mejores lineas que he escrito en mi vida
    glm::vec3 FIXED_NEXT_POSITION = nextPosition+(camPosition-nextPosition)*0.2f;
    if(dynWorld->RayCastTest(FIXED_NEXT_POSITION,camPosition,pos_on_collision)){
        Engine->setPosition(cam, pos_on_collision);
        Pos = pos_on_collision;
    }
}

glm::vec3 CCamera::getOffsetPositionVector(){
    return offsetPositionVector;
}

glm::vec3 CCamera::getCameraPosition(){
    return Pos;
}

glm::vec3 CCamera::getCameraRotation(){
    return Rot;
}

glm::vec3 CCamera::getlastHeroPosition(){
    return lastHeroPosition;
}

glm::vec3 CCamera::getCameraPositionBeforeLockRotation(){
    return cameraPositionBeforeLockRotation;
}

void CCamera::setCameraPositionBeforeLockRotation(glm::vec3 vector){
    cameraPositionBeforeLockRotation = vector;
}

void CCamera::moveCameraPosition(glm::vec3 _offPos){
    Pos += _offPos;
    Engine->setPosition(cam, Pos);
}
