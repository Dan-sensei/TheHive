#include "CCamera.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include <Bullet/ggDynWorld.hpp>

#define PI                  3.14159265358979323846264338
#define DEGREES_TO_RADIANS  PI/180.f
#define CAMERA_ATENUATION   7.f
#define HEIGHT              0.4
#define RADIUS              2.0


#define VERTICAL_ANGLE_LIMIT 25

#define VERT_ANG_LIM_RAD VERTICAL_ANGLE_LIMIT*DEGREES_TO_RADIANS
#define Y_OFF sin(-VERT_ANG_LIM_RAD)
#define X_OFF cos(-VERT_ANG_LIM_RAD)

CCamera::CCamera(int8_t _b)
:Target(nullptr), Engine(nullptr), cam(nullptr),
InvertCamera(_b)
{
    CurrentUpdate = &CCamera::FollowTarget;
    LastFreeCameraPosition = glm::vec3(150, 30, -60);
}


CCamera::~CCamera(){
}

void CCamera::Init(){
    Engine = Singleton<Omicron>::Instance();
    dynWorld = Singleton<ggDynWorld>::Instance();
    cam = Engine->getCamera();

    collision = false;


    screenW = Engine->getScreenWidth();
    screenH = Engine->getScreenHeight();

    Engine->getCursorPosition(prevX, prevY);
    t = 0;
    p = 0;
}
//
void CCamera::setTarget(CTransform *T) {
    Target = T;
}
void CCamera::resetMouse() {
    double x, y;
    Engine->getCursorPosition(x, y);

    prevX = x;
    prevY = y;
}

void CCamera::CameraUpdate(){
    (this->*CurrentUpdate)();
}

void CCamera::FollowTarget(){
    double x, y;
    Engine->getCursorPosition(x, y);
    t += (prevX - x) * 0.005f;
    p += (y - prevY) * 0.005f * -InvertCamera;

    prevX = x;
    prevY = y;

    if(t < 0) t = 2*PI;
    else if(t > 2*PI) t = 0;

    if(p < -PI/2+0.2) p = -PI/2+0.2;
    else if(p > 0.204999) p = 0.204999;

    CameraTarget = Target->getPosition();

    float cos_ = X_OFF;
    float sin_ = Y_OFF;
    if(p > -VERT_ANG_LIM_RAD){
        cos_ = cos(p);
        sin_ = sin(p);
    }

    CurrentPosition.x = CameraTarget.x + 1 * sin(t)*cos_;
    CurrentPosition.y = CameraTarget.y + 1 + sin_;
    CurrentPosition.z = CameraTarget.z + 1 * cos(t)*cos_;

    CameraTarget.x += cos(t)*0.75;
    CameraTarget.z -= sin(t)*0.75;
    CameraTarget.y -= sin(p)*1.5;


    Engine->setPosition(cam, CurrentPosition);
    static_cast<TCamara*>(cam->getEntidad())->setTarget(CameraTarget);
}


void CCamera::fixCameraPositionOnCollision(glm::vec3 &nextPosition){
    glm::vec3 camPosition = CurrentPosition;
    // Las dos mejores lineas que he escrito en mi vida
    glm::vec3 FIXED_NEXT_POSITION = nextPosition+(camPosition-nextPosition)*0.2f;
    if(dynWorld->RayCastTest(FIXED_NEXT_POSITION,camPosition,pos_on_collision)){
        Engine->setPosition(cam, pos_on_collision);
        CurrentPosition = pos_on_collision;
    }
}

void CCamera::getDirectionVector(glm::vec3 &Output){
    Output = CurrentPosition - CameraTarget;
    Output.y = 0;
}

glm::vec3 CCamera::getCameraPosition(){
    return CurrentPosition;
}

void CCamera::moveCameraPosition(glm::vec3 _offPos){
    CurrentPosition += _offPos;
    Engine->setPosition(cam, CurrentPosition);
}

glm::vec3 CCamera::getTargetPosition(){
    return CameraTarget;
}

void CCamera::ToogleFreeCamera(){
    if(CurrentUpdate == &CCamera::FollowTarget){
        CurrentUpdate = &CCamera::FreeCamera;
        Engine->setPosition(cam, LastFreeCameraPosition);
        t = 0;
        p = 0;
    }
    else{
        CurrentUpdate = &CCamera::FollowTarget;
        t = 0;
        p = 0;
    }
}

void CCamera::FreeCamera(){
    double x, y;
    Engine->getCursorPosition(x, y);
    t += (prevX - x) * 0.005f;
    p += (y - prevY) * 0.005f * InvertCamera;

    prevX = x;
    prevY = y;

    if(t < 0) t = 2*PI;
    else if(t > 2*PI) t = 0;

    if(p < -PI/2+0.2) p = -PI/2+0.2;
    else if(p > PI/2 - 0.2) p = PI/2 - 0.2;

    #define SPEED 0.5
    if(Engine->key(gg::W)){
        glm::vec3 dir = glm::normalize(CameraTarget - LastFreeCameraPosition);
        LastFreeCameraPosition += glm::vec3(dir.x * SPEED, dir.y * SPEED, dir.z * SPEED);
    }
    else if(Engine->key(gg::S)){
        glm::vec3 dir = glm::normalize(CameraTarget - LastFreeCameraPosition);
        LastFreeCameraPosition -= glm::vec3(dir.x * SPEED, dir.y * SPEED, dir.z * SPEED);
    }
    if(Engine->key(gg::A)){
        glm::vec3 dir = CameraTarget - LastFreeCameraPosition;
        glm::vec3 ppV = glm::normalize(glm::vec3(-dir.z,0,dir.x));
        LastFreeCameraPosition -= glm::vec3(ppV.x * SPEED, 0, ppV.z * SPEED);
    }
    else if(Engine->key(gg::D)){
        glm::vec3 dir = CameraTarget - LastFreeCameraPosition;
        glm::vec3 ppV = glm::normalize(glm::vec3(-dir.z,0,dir.x));
        LastFreeCameraPosition += glm::vec3(ppV.x * SPEED, 0, ppV.z * SPEED);
    }

    CameraTarget.x = LastFreeCameraPosition.x + 1 * sin(t)*cos(p);
    CameraTarget.y = LastFreeCameraPosition.y + 1 * sin(p);
    CameraTarget.z = LastFreeCameraPosition.z + 1 * cos(t)*cos(p);

    Engine->setPosition(cam, LastFreeCameraPosition);
    static_cast<TCamara*>(cam->getEntidad())->setTarget(CameraTarget);
}

