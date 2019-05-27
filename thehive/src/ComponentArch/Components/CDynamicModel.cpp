#include "CDynamicModel.hpp"
#include <ComponentArch/ObjectManager.hpp>
#include "CTransform.hpp"

CDynamicModel::CDynamicModel(StandardNode* FATHER, ZMaterial* material)
:DynamicModel(nullptr), cTransform(nullptr), CurrentAnimation(0), Auto(false)
{
    Surreal = Singleton<Omicron>::Instance();
    DynamicModel = Surreal->CreateDynamicMesh(FATHER);
    Surreal->bindMaterialToDynamicMesh(DynamicModel, material);
    DynamicModelEntity = static_cast<ZDynamicMesh*>(DynamicModel->getEntidad());
}

CDynamicModel::CDynamicModel(const CDynamicModel &orig){
    DynamicModel = orig.DynamicModel;
}

CDynamicModel::~CDynamicModel() {
    Surreal->deleteLeafNode(DynamicModel);
}

void CDynamicModel::Init() {
    MHandler_SETPTRS();
}

void CDynamicModel::setVisibility(bool flag) {
    DynamicModel->getPadre()->getPadre()->setVisibility(flag);
}

void CDynamicModel::AddAnimation(ZAnimationData* Anim) {
    DynamicModelEntity->AddAnimation(Anim);
}
void CDynamicModel::setStepDistance(float D){
    DynamicModelEntity->setStepDistance(D);
}

void CDynamicModel::ToggleAnimation(uint8_t Anim, float Time, bool NeedsToComplete, bool _Auto) {
    if(DynamicModelEntity->SwitchAnimation(Anim, Time, NeedsToComplete, _Auto)){
        CurrentAnimation = Anim;
        Auto = _Auto;
    }
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

        if(!Auto)
            DynamicModelEntity->setPosForStep(glm::vec2(cTransform->getPosition().x, cTransform->getPosition().z));
    }
}

gg::EMessageStatus CDynamicModel::MHandler_SETPTRS(){
    //  We check if this entity has the TRANSFORM component
    cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
    return gg::ST_TRUE;
}
