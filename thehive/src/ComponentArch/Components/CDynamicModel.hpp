#ifndef _CDYNAMICMODEL_H
#define _CDYNAMICMODEL_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <Omicron/ZMESHES/ZStaticMesh.hpp>
#include <Omicron/ZMaterial.hpp>
#include <map>
#include <iostream>
#include <Singleton.hpp>
#include <Omicron/Omicron.hpp>

#include <Omicron/ZMESHES/ZAnimationData.hpp>
#include <AnimationLUT.hpp>

class CTransform;

class CDynamicModel : public IComponent {
    public:
        CDynamicModel(StandardNode* FATHER, ZMaterial* material);
        CDynamicModel(const CDynamicModel &orig);
        virtual ~CDynamicModel();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void Update();

        void AddAnimation(ZAnimationData* Anim);
        void ToggleAnimation(uint8_t Anim, float Time, bool NeedsToComplete = false,  bool _Auto = true);
        void setStepDistance(float D);

        inline uint8_t getCurrentAnimation(){ return CurrentAnimation; };
        inline bool getAnimationPlayed(){ return static_cast<ZDynamicMesh*>(DynamicModel->getEntidad())->getAnimationPlayed(); };

        //  Handler
        gg::EMessageStatus MHandler_SETPTRS();
        void setVisibility(bool flag);


    private:
        ZNode* DynamicModel;
        ZDynamicMesh* DynamicModelEntity;
        Omicron* Surreal;

        CTransform* cTransform;
        uint8_t CurrentAnimation;
        bool Auto;
};

#endif
