#include "CRenderable_3D.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include "CTransform.hpp"

CRenderable_3D::CRenderable_3D(const std::string &pathToModel, ZMaterial* material)
:_3DModel(nullptr), cTransform(nullptr)
{
    Surreal = Singleton<SurrealEngine>::Instance();
    _3DModel = Surreal->crearMalla(pathToModel.c_str());
    Surreal->bindMaterialToMesh(_3DModel, material);
}

CRenderable_3D::CRenderable_3D(const CRenderable_3D &orig){
    _3DModel = orig._3DModel;
}

CRenderable_3D::~CRenderable_3D() {
    Surreal->deleteLeafNode(_3DModel);
}

void CRenderable_3D::Init(){

    MHandler_SETPTRS();
}

void CRenderable_3D::setVisibility(bool flag){
    _3DModel->getPadre()->getPadre()->setVisibility(flag);
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
        Surreal->setPosition(_3DModel, cTransform->getPosition());
        Surreal->setRotation(_3DModel, cTransform->getRotation());
    }
}

gg::EMessageStatus CRenderable_3D::MHandler_SETPTRS(){
    //  We check if this entity has the TRANSFORM component
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    return gg::ST_TRUE;
}
