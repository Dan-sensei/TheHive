#include "CRenderable_3D.hpp"
#include "Singleton.hpp"
#include "ObjectManager.hpp"
#include "GameEngine.hpp"

CRenderable_3D::CRenderable_3D()
:_3DModel()
{

}

CRenderable_3D::CRenderable_3D(const CRenderable_3D &orig){
    _3DModel = orig._3DModel;
}

CRenderable_3D::~CRenderable_3D() {

}

void CRenderable_3D::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::KEYBOARD, gg::M_UPDATE);
}

void CRenderable_3D::initializeComponentData(){
    Material moradoDeLos80("assets/Models/obradearte/prueba1.png");

    _3DModel = Singleton<GameEngine>::Instance()->createModel("assets/Models/obradearte/algo.obj");
    _3DModel.assignMaterial(moradoDeLos80);
}

gg::EMessageStatus CRenderable_3D::processMessage() {

    GameEngine* engine = Singleton<GameEngine>::Instance();
    CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    if(cTransform){

        _3DModel.setPosition(cTransform->getPosition());

        return gg::ST_TRUE;
    }

    return gg::ST_ERROR;
}
