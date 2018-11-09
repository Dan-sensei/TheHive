#include "CRenderable_3D.hpp"
#include <Singleton.hpp>
#include <ComponentArch/ObjectManager.hpp>
#include <ComponentArch/InitStructs.hpp>
#include <GameEngine/GameEngine.hpp>

CRenderable_3D::CRenderable_3D()
:_3DModel(), cTransform(nullptr)
{}

CRenderable_3D::CRenderable_3D(const CRenderable_3D &orig){
    _3DModel = orig._3DModel;
}

CRenderable_3D::~CRenderable_3D() {}

void CRenderable_3D::initComponent() {
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RENDERABLE_3D, gg::M_UPDATE);
    Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::RENDERABLE_3D, gg::M_SETPTRS);
}


void CRenderable_3D::initializeComponentData(const void* data){
    if(data){
        InitCRenderable_3D* cData = (InitCRenderable_3D*)data;

        Singleton<GameEngine>::Instance()->createModel(_3DModel, cData->pathToModel);
        _3DModel.assignMaterial(cData->material);
    }
    MHandler_SETPTRS();
}


gg::EMessageStatus CRenderable_3D::processMessage(const Message &m) {

    if      (m.mType == gg::M_UPDATE)   return MHandler_UPDATE();
    else if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

gg::EMessageStatus CRenderable_3D::MHandler_UPDATE(){
    if(cTransform){
        //  If exists, we get its position, and asign it to the _3DModel
        _3DModel.setPosition(cTransform->getPosition());
        _3DModel.setRotation(cTransform->getRotation());

        return gg::ST_TRUE;
    }

    return gg::ST_ERROR;
}

gg::EMessageStatus CRenderable_3D::MHandler_SETPTRS(){
    //  We check if this entity has the TRANSFORM component
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    return gg::ST_TRUE;
}
