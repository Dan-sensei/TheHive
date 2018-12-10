#include "CCamera.hpp"
#include <ComponentArch/ObjectManager.hpp>

#define PI                  3.1415926535897932384626433832795028841971693993751058209749445923078164062
#define DEGREES_TO_RADIANS  PI/180.f
#define CAMERA_ATENUATION   7.f
#define HEIGHT              0.4
#define RADIUS              2.5

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

    float _S = 0.4;
    lastHeroPosition = mod->getPosition();
    cameraPositionBeforeLockRotation = Engine->getCamera()->getPosition();

    entCollisions = Manager->createEntity();
    CTransform* Transform               = new CTransform(gg::Vector3f(0, 0, 0), gg::Vector3f(0, 0, 0));
    Manager->addComponentToEntity(Transform,        gg::TRANSFORM, entCollisions);
    // CRigidBody* RigidBody               = new CRigidBody(true, false,"", 0,0,0, _S,_S,_S, 50, 0,0,0);
    CRigidBody* RigidBody               = new CRigidBody(true, 0,0,0, _S,_S,_S);
    Manager->addComponentToEntity(RigidBody,        gg::RIGID_BODY, entCollisions);

    collTF = Transform;
    collRB = RigidBody;

    CRigidBody *rbEnt = static_cast<CRigidBody*>(Manager->getComponent(gg::RIGID_BODY,getEntityID()));
    collRB->setIgnoreCollisionCheck1st(rbEnt, true);

    collision = false;
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
    float screenW = static_cast<int>(Engine->getScreenWidth())/2;
    float screenH = static_cast<int>(Engine->getScreenHeight())/2;

    // Set the coordinates to an absolute 0 on the center of the screen
    // Set the mouse new coordinate to the center(0,0)
    float vX = Engine->getCursorX() - screenW;
    float vY = Engine->getCursorY() - screenH;
    if(daniNoSabeProgramar)
        vY = -vY;
    Engine->setCursorPosition(static_cast<int>(screenW),static_cast<int>(screenH));

    gg::Vector3f backupRotation = cam->getRotation();
    gg::Vector3f newRotation = backupRotation;
    newRotation.X += vY/CAMERA_ATENUATION;
    newRotation.Y += vX/CAMERA_ATENUATION;
    newRotation.Z  = 0;

    /////////////////////////////////////////////////////////////////
    // HORIZONTAL AXIS
    /////////////////////////////////////////////////////////////////
    // Now is applied the rotation on the HORIZONTAL AXIS
    // Having the rotation center on the camera position
    gg::Vector3f nextModelPosition = cam->getPosition();

    float dist = RADIUS;
    float angle = newRotation.Y*DEGREES_TO_RADIANS;
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
    gg::Vector3f finalCameraPosition = nextModelPosition;

    angle = -newRotation.X*DEGREES_TO_RADIANS;
    float   newY = dist * sin(angle);
            newZ = dist * cos(angle);

    finalCameraPosition.Y += newY;
    finalCameraPosition.X += newZ;

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


    // -------------------------------------------
    // Colisiones de la camara
    // -------------------------------------------
    camPosition = cam->getPosition();

    // Las dos mejores lineas que he escrito en mi vida
    gg::Vector3f FIXED_NEXT_POSITION = nextPosition+(camPosition-nextPosition)*0.2;
    if(Singleton<ggDynWorld>::Instance()->RayCastTest(FIXED_NEXT_POSITION,camPosition,pos_on_collision)){
        cam->setPosition(pos_on_collision);
    }

    // Perpendicular vector to set an offset to the right
    camPosition = cam->getPosition();
    gg::Vector3f ppV(
        nextPosition.Z-camPosition.Z,
        0,
        -(nextPosition.X-camPosition.X)
    );
    ppV = gg::Normalice(ppV);
    offsetPositionVector = ppV;

    moveCameraPosition(ppV);

    // Call to updateAbsolutePosition() to avoid perspective
    // and camera position problems
    // ¡¡¡¡ THIS HAS TO BE THE LAST FUNCTION TO CALL !!!!
    cam->updateAbsolutePosition();

    // SECOND set the camera rotation
    if(newRotation.X >= -30 && newRotation.X <= 60)
        cam->setRotation(newRotation);
    else
        cam->setRotation(backupRotation);

    // If heroRotation is FALSE, the hero won't move with the camera rotation
    if(heroRotation){
        cameraPositionBeforeLockRotation = cam->getPosition();
        // mod->setRotation(gg::Vector3f(0,newRotation.Y,0));
    }

}

gg::Vector3f CCamera::getOffsetPositionVector(){
    return offsetPositionVector;
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

void CCamera::moveCameraPosition(gg::Vector3f _offPos){
    cam->setPosition(
        gg::Vector3f(
            cam->getPosition().X + _offPos.X,
            cam->getPosition().Y + _offPos.Y,
            cam->getPosition().Z + _offPos.Z
        )
    );
}
