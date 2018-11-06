#include "CRenderable_3D.hpp"
#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/InitStructs.hpp>
#include <GameEngine/GameEngine.hpp>

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

    InitCRenderable_3D* cData = (InitCRenderable_3D*)data;

    _3DModel = Singleton<GameEngine>::Instance()->createModel(cData->pathToModel);
    _3DModel.assignMaterial(cData->material);
}

/*      Init     */
void CRenderable_3D::initAfterComponentAssigment() {
    std::cout << "Init CRenderable" << '\n';

}

gg::EMessageStatus CRenderable_3D::processMessage() {

    //  We check if this entity has the TRANSFORM component
    CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));

    if(cTransform){
        //  If exists, we get its position, and asign it to the _3DModel
        _3DModel.setPosition(cTransform->getPosition());

        return gg::ST_TRUE;
    }

    return gg::ST_ERROR;
}
