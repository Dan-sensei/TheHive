#include "CKeyboard.hpp"
#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>

#define MOVEMENT_SPEED 1.f
#define RUNNING_SPEED MOVEMENT_SPEED*1.05f
#define DASH_SPEED MOVEMENT_SPEED*4.f
#define MAX_ANGLE 12.f

#define DASH_KEY gg::GG_F
#define ROTATE_KEY gg::GG_LCONTROL
#define RUN_KEY gg::GG_LSHIFT

CKeyboard::CKeyboard(){

}

CKeyboard::CKeyboard(const CKeyboard &orig){

}

CKeyboard::~CKeyboard() {

}

void CKeyboard::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_UPDATE);
}

gg::EMessageStatus CKeyboard::processMessage() {


    GameEngine* engine = Singleton<GameEngine>::Instance();

    //  We check if this entity has the TRANSFORM component
    CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    if(cTransform){
        CCamera *camera = dynamic_cast<CCamera*>(Singleton<ObjectManager>::Instance()->getComponent(gg::CAMERA, getEntityID()));
        if(camera){
            //  If exists, we get its position
            gg::Vector3f nextPosition = camera->getLastCameraPosition();

            gg::Vector3f tV = camera->getCameraTarget();
            tV.X = fmod(tV.X -= nextPosition.X,MOVEMENT_SPEED);
            tV.Y = fmod(tV.Y -= nextPosition.Y,MOVEMENT_SPEED);
            tV.Z = fmod(tV.Z -= nextPosition.Z,MOVEMENT_SPEED);
            // tV.X -= nextPosition.X;
            // tV.Y -= nextPosition.Y;
            // tV.Z -= nextPosition.Z;
            std::cout << tV.X << "," << tV.Y << "," << tV.Z << '\n';
            // std::cout << fmod(tV.X+tV.Z,1) << '\n';

            bool heroRotation = true;

            if(engine->key(gg::GG_W)){
                nextPosition.Z += MOVEMENT_SPEED;
                if(engine->key(DASH_KEY))
                    nextPosition.Z += DASH_SPEED;
                else if(engine->key(RUN_KEY))
                    nextPosition.Z += RUNNING_SPEED;
            }
            else if(engine->key(gg::GG_S)){
                nextPosition.Z -= MOVEMENT_SPEED;
                if(engine->key(DASH_KEY))
                    nextPosition.Z -= DASH_SPEED;
                else if(engine->key(RUN_KEY))
                    nextPosition.Z -= RUNNING_SPEED;
            }

            if(engine->key(gg::GG_A)){
                nextPosition.X -= MOVEMENT_SPEED;
                if(engine->key(DASH_KEY))
                    nextPosition.X -= DASH_SPEED;
                else if(engine->key(RUN_KEY))
                    nextPosition.X -= RUNNING_SPEED;
            }
            else if(engine->key(gg::GG_D)){
                nextPosition.X += MOVEMENT_SPEED;
                if(engine->key(DASH_KEY))
                    nextPosition.X += DASH_SPEED;
                else if(engine->key(RUN_KEY))
                    nextPosition.X += RUNNING_SPEED;
            }

            // if(engine->key(gg::GG_W)){
            //     nextPosition.X -= tV.X;
            //     nextPosition.Z -= tV.Z;
            // }
            // else if(engine->key(gg::GG_S)){
            //     nextPosition.X += tV.X;
            //     nextPosition.Z += tV.Z;
            // }
            //
            // if(engine->key(gg::GG_A)){
            //     nextPosition.X -= tV.X;
            //     nextPosition.Z += tV.Z;
            // }
            // else if(engine->key(gg::GG_D)){
            //     nextPosition.X += tV.X;
            //     nextPosition.Z -= tV.Z;
            // }

            if(engine->key(ROTATE_KEY))
                heroRotation = false;

            // And we update it accoding to the keyboard input
            // cTransform->setPosition(nextPosition);
            camera->updateCameraTarget(getEntityID(),nextPosition,heroRotation);

            return gg::ST_TRUE;
        }
    }

    return gg::ST_ERROR;
}
