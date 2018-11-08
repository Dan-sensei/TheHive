#include "CRenderable_3D.hpp"
#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/InitStructs.hpp>
#include <GameEngine/GameEngine.hpp>

CRenderable_3D::CRenderable_3D()
:_3DModel(), cTransform(nullptr)
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
    if(data){
        InitCRenderable_3D* cData = (InitCRenderable_3D*)data;

        _3DModel = Singleton<GameEngine>::Instance()->createModel(cData->pathToModel);
        _3DModel.assignMaterial(cData->material);
    }

    //  We check if this entity has the TRANSFORM component
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
}


gg::EMessageStatus CRenderable_3D::processMessage() {

    if(cTransform){
        //  If exists, we get its position, and asign it to the _3DModel
        _3DModel.setPosition(cTransform->getPosition());
        _3DModel.setRotation(cTransform->getRotation());

        return gg::ST_TRUE;
    }

    return gg::ST_ERROR;
}
