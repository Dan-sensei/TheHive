#include "CRenderable_3D.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include <GameEngine/GameEngine.hpp>
#include "CTransform.hpp"

CRenderable_3D::CRenderable_3D(const std::string &pathToModel, const Material &material)
:_3DModel(), cTransform(nullptr)
{
    Singleton<GameEngine>::Instance()->createModel(_3DModel, pathToModel);
    _3DModel.assignMaterial(material);
}

CRenderable_3D::CRenderable_3D(const CRenderable_3D &orig){
    _3DModel = orig._3DModel;
}

CRenderable_3D::~CRenderable_3D() {}
//


void CRenderable_3D::Init(){

    MHandler_SETPTRS();
}

void CRenderable_3D::setVisibility(bool flag){
    _3DModel.setVisibility(flag);
}

gg::EMessageStatus CRenderable_3D::processMessage(const Message &m) {

    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS();

    return gg::ST_ERROR;
}


//  Message handler functions_______________________________________________________________
//|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |

void CRenderable_3D::Update(){
    if(cTransform){
        //  If exists, we get its position, and asign it to the _3DModel
        _3DModel.setPosition(cTransform->getPosition());
        _3DModel.setRotation(cTransform->getRotation());
    }
}

gg::EMessageStatus CRenderable_3D::MHandler_SETPTRS(){
    //  We check if this entity has the TRANSFORM component
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    return gg::ST_TRUE;
}
