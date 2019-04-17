#include "CDynamicModel.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include "CTransform.hpp"

CDynamicModel::CDynamicModel(ZMaterial* material)
:DynamicModel(nullptr), cTransform(nullptr), CurrentAnimation(0)
{
    Surreal = Singleton<Omicron>::Instance();
    DynamicModel = Surreal->CreateDynamicMesh();
    Surreal->bindMaterialToDynamicMesh(DynamicModel, material);
}

CDynamicModel::CDynamicModel(const CDynamicModel &orig){
    DynamicModel = orig.DynamicModel;
}

CDynamicModel::~CDynamicModel() {
    Surreal->deleteLeafNode(DynamicModel);
}

void CDynamicModel::Init(){
    MHandler_SETPTRS();
}

void CDynamicModel::setVisibility(bool flag){
    DynamicModel->getPadre()->getPadre()->setVisibility(flag);
}

void CDynamicModel::AddAnimation(ZAnimationData* Anim){
    static_cast<ZDynamicMesh*>(DynamicModel->getEntidad())->AddAnimation(Anim);
}

void CDynamicModel::ToggleAnimation(uint8_t Anim, float Time){
    CurrentAnimation = Anim;
    static_cast<ZDynamicMesh*>(DynamicModel->getEntidad())->SwitchAnimation(Anim, Time);
}


gg::EMessageStatus CDynamicModel::processMessage(const Message &m) {
    if (m.mType == gg::M_SETPTRS)  return MHandler_SETPTRS();
    return gg::ST_ERROR;
}

void CDynamicModel::Update(){
    if(cTransform){
        //  If exists, we get its position, and asign it to the DynamicModel
        Surreal->setPosition(DynamicModel, cTransform->getPosition());
        Surreal->setRotation(DynamicModel, cTransform->getRotation());
    }
}

gg::EMessageStatus CDynamicModel::MHandler_SETPTRS(){
    //  We check if this entity has the TRANSFORM component
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    return gg::ST_TRUE;
}
