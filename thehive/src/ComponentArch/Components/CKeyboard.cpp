#include "CKeyboard.hpp"
#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>

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
            bool heroRotation = true;

            // TODO:
            //      MEJORAR la forma en la que se calcula el angulo de la camara
            //      CAMBIAR la forma en la que se mueve CUANDO EL CTRL ESTA PULSADO

            // Vector direccion camara-heroe
            gg::Vector3f cV = camera->getCameraPosition();
            gg::Vector3f hV = cTransform->getPosition();
                cV.X -= hV.X;
                cV.Y -= hV.Y;
                cV.Z -= hV.Z;

            float length = sqrt(cV.X*cV.X + cV.Y*cV.Y + cV.Z*cV.Z);
                cV.X /= length;
                cV.Y /= length;
                cV.Z /= length;

            // Vector perpendicular al vector direccion
            gg::Vector3f ppV(-cV.Z,0,cV.X);

            gg::Vector2f DASH_SPEED(cV.X*4,cV.Z*4);
            gg::Vector2f RUNNING_SPEED(cV.X*1.05,cV.Z*1.05);

            if(engine->key(gg::GG_W)){
                nextPosition.X -= cV.X;
                nextPosition.Z -= cV.Z;
                if(engine->key(DASH_KEY)){
                    nextPosition.X -= DASH_SPEED.X;
                    nextPosition.Z -= DASH_SPEED.Y;
                }
                else if(engine->key(RUN_KEY)){
                    nextPosition.X -= RUNNING_SPEED.X;
                    nextPosition.Z -= RUNNING_SPEED.Y;
                }
            }
            else if(engine->key(gg::GG_S)){
                nextPosition.X += cV.X;
                nextPosition.Z += cV.Z;
                if(engine->key(DASH_KEY)){
                    nextPosition.X += DASH_SPEED.X;
                    nextPosition.Z += DASH_SPEED.Y;
                }
                else if(engine->key(RUN_KEY)){
                    nextPosition.X += RUNNING_SPEED.X;
                    nextPosition.Z += RUNNING_SPEED.Y;
                }
            }

            DASH_SPEED = gg::Vector2f(ppV.X*4,ppV.Z*4);
            RUNNING_SPEED =  gg::Vector2f(ppV.X*1.05,ppV.Z*1.05);

            if(engine->key(gg::GG_A)){
                nextPosition.X -= ppV.X;
                nextPosition.Z -= ppV.Z;
                if(engine->key(DASH_KEY)){
                    nextPosition.X -= DASH_SPEED.X;
                    nextPosition.Z -= DASH_SPEED.Y;
                }
                else if(engine->key(RUN_KEY)){
                    nextPosition.X -= RUNNING_SPEED.X;
                    nextPosition.Z -= RUNNING_SPEED.Y;
                }
            }
            else if(engine->key(gg::GG_D)){
                nextPosition.X += ppV.X;
                nextPosition.Z += ppV.Z;
                if(engine->key(DASH_KEY)){
                    nextPosition.X += DASH_SPEED.X;
                    nextPosition.Z += DASH_SPEED.Y;
                }
                else if(engine->key(RUN_KEY)){
                    nextPosition.X += RUNNING_SPEED.X;
                    nextPosition.Z += RUNNING_SPEED.Y;
                }
            }

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
