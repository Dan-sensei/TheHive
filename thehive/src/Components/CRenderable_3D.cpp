#include "CRenderable_3D.hpp"
#include <Singleton.hpp>
#include <ObjectManager.hpp>
#include <GameEngine.hpp>
#include <InitStructs.hpp>

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
    //  We wait for the M_UPDATE message
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RENDERABLE_3D, gg::M_UPDATE);
}

void CRenderable_3D::initializeComponentData(const void* data){

    ICRenderable_3D* cData = (ICRenderable_3D*)data;

    _3DModel = Singleton<GameEngine>::Instance()->createModel(cData->pathToModel);
    _3DModel.assignMaterial(cData->material);
}

gg::EMessageStatus CRenderable_3D::processMessage() {

    GameEngine* engine = Singleton<GameEngine>::Instance();

    //  We check if this entity has the TRANSFORM component
    CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    if(cTransform){
        //  If exists, we get its position, and asign it to the _3DModel
        _3DModel.setPosition(cTransform->getPosition());

        return gg::ST_TRUE;
    }

    return gg::ST_ERROR;
}
