#include "CKeyboard.hpp"
#include "Singleton.hpp"
#include "ObjectManager.hpp"
#include "GameEngine.hpp"

#define MOVEMENT_SPEED 1.f

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

    CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    if(cTransform){
        gg::Vector3f nextPosition = cTransform->getPosition();

        if(engine->key(gg::GG_W))
            nextPosition.Z += MOVEMENT_SPEED;
        else if(engine->key(gg::GG_S))
            nextPosition.Z -= MOVEMENT_SPEED;

        if(engine->key(gg::GG_A))
            nextPosition.X -= MOVEMENT_SPEED;
        else if(engine->key(gg::GG_D))
            nextPosition.X += MOVEMENT_SPEED;

        cTransform->setPosition(nextPosition);

        return gg::ST_TRUE;
    }

    return gg::ST_ERROR;
}
