#include "CKeyboard.hpp"
#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>

#define MOVEMENT_SPEED 1.f

CKeyboard::CKeyboard(){

}

CKeyboard::~CKeyboard() {

}

void CKeyboard::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_UPDATE);
}

void CKeyboard::initializeComponentData(const void* data){

}

/*      Init     */
void CKeyboard::initAfterComponentAssigment() {
    std::cout << "Init Component" << '\n';

}

gg::EMessageStatus CKeyboard::processMessage() {


    GameEngine* engine = Singleton<GameEngine>::Instance();

    //  We check if this entity has the TRANSFORM component
    //CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    //if(cTransform){
        CCamera *camera = static_cast<CCamera*>(Singleton<ObjectManager>::Instance()->getComponent(gg::CAMERA, getEntityID()));
        if(camera){
            //  If exists, we get its position
            gg::Vector3f nextPosition = camera->getLastCameraPosition();

            if(engine->key(gg::GG_W))
            nextPosition.Z += MOVEMENT_SPEED;
            else if(engine->key(gg::GG_S))
            nextPosition.Z -= MOVEMENT_SPEED;

            if(engine->key(gg::GG_A))
            nextPosition.X -= MOVEMENT_SPEED;
            else if(engine->key(gg::GG_D))
            nextPosition.X += MOVEMENT_SPEED;

            // And we update it accoding to the keyboard input
            // cTransform->setPosition(nextPosition);
            camera->updateCameraTarget(getEntityID(),nextPosition);

            return gg::ST_TRUE;
        }
    //}

    return gg::ST_ERROR;
}
