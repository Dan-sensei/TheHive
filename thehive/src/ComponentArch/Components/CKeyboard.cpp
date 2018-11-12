#include "CKeyboard.hpp"
#include <Singleton.hpp>
#include <GameEngine/GameEngine.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <Util.hpp>

#define MAX_ANGLE       12.f

#define ROTATE_KEY      gg::GG_LCONTROL
#define DASH_KEY        gg::GG_ALT
#define RUN_KEY         gg::GG_LSHIFT
#define JUMP_KEY        gg::GG_SPACEBAR

#define DASH_FACTOR     1.2f
#define RUN_FACTOR      1.1f

CKeyboard::CKeyboard()
:cTransform(nullptr)
{

}

CKeyboard::~CKeyboard() {

}

void CKeyboard::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_SETPTRS);

}

void CKeyboard::initializeComponentData(const void* data){
    //  We check if this entity has the TRANSFORM component
    engine = Singleton<GameEngine>::Instance();
    camera = static_cast<CCamera*>(Singleton<ObjectManager>::Instance()->getComponent(gg::CAMERA, getEntityID()));
    MHandler_SETPTRS();
}


gg::EMessageStatus CKeyboard::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE  ();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS ();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CKeyboard::MHandler_SETPTRS(){
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    cRigidBody = static_cast<CRigidBody*>(Singleton<ObjectManager>::Instance()->getComponent(gg::RIGID_BODY, getEntityID()));

    return gg::ST_TRUE;
}

gg::EMessageStatus CKeyboard::MHandler_UPDATE(){

    if(!cTransform || !camera || !cRigidBody)  return gg::ST_ERROR;

    //  If exists, we get its position
    gg::Vector3f nextPosition = camera->getlastHeroPosition();
    bool heroRotation = true;

    // Vector direccion camara-heroe
    gg::Vector3f cV = camera->getCameraPositionBeforeLockRotation();
    gg::Vector3f cV2 = cV;
    gg::Vector3f hV = cRigidBody->getBodyPosition();
        cV.X -= hV.X;
        cV.Y -= hV.Y;
        cV.Z -= hV.Z;

    float length = sqrt(cV.X*cV.X + cV.Y*cV.Y + cV.Z*cV.Z);
        cV.X /= length;
        cV.Y /= length;
        cV.Z /= length;

    // Vector perpendicular al vector direccion
    gg::Vector3f ppV(-cV.Z,0,cV.X);

    // Vector que tendrá el impulso para aplicar al body
    gg::Vector3f impulse;

    if(engine->key(gg::GG_W)){
        impulse = gg::Vector3f(-cV.X,0,-cV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X-=cV.X;
        //     cV2.Z-=cV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // };
    }
    else if(engine->key(gg::GG_S)){
        impulse = gg::Vector3f(+cV.X,0,+cV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X+=cV.X;
        //     cV2.Z+=cV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // }
    }

    if(engine->key(gg::GG_A)){
        impulse = gg::Vector3f(-ppV.X,0,-ppV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X-=ppV.X;
        //     cV2.Z-=ppV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // };
    }
    else if(engine->key(gg::GG_D)){
        impulse = gg::Vector3f(+ppV.X,0,+ppV.Z);
        // if(engine->key(ROTATE_KEY)){
        //     cV2.X+=ppV.X;
        //     cV2.Z+=ppV.Z;
        //     camera->setCameraPositionBeforeLockRotation(cV2);
        // }
    }
    if(engine->key(ROTATE_KEY))
        heroRotation = false;

    if(engine->key(DASH_KEY)){
        impulse.X *= 1.05;
        impulse.Z *= 1.05;
    }
    else if(engine->key(RUN_KEY)){
        impulse.X *= 1.02;
        impulse.Z *= 1.02;
    }

    if(engine->key(JUMP_KEY)){
        impulse.Y = 5;
    }

    // cRigidBody->applyCentralForce(impulse);
    cRigidBody->applyCentralImpulse(impulse);

    // And we update it accoding to the keyboard input
    camera->updateCameraTarget(cRigidBody->getBodyPosition(),heroRotation);

    return gg::ST_TRUE;

}
