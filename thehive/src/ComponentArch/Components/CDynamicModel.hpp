#ifndef _CDYNAMICMODEL_H
#define _CDYNAMICMODEL_H

#include <ComponentArch/IComponent.hpp>
#include <ComponentArch/Message.hpp>
#include <SurrealEngine/ZStaticMesh.hpp>
#include <SurrealEngine/ZMaterial.hpp>
#include <map>
#include <iostream>
#include <Singleton.hpp>
#include <SurrealEngine/SurrealEngine.hpp>

#include <SurrealEngine/ZAnimationData.hpp>
#include <AnimationLUT.hpp>

class CTransform;

class CDynamicModel : public IComponent {
    public:
        CDynamicModel(ZMaterial* material);
        CDynamicModel(const CDynamicModel &orig);
        virtual ~CDynamicModel();

        // Functions of IComponent
        virtual gg::EMessageStatus processMessage(const Message &m);
        virtual void Init();
        virtual void Update();

        void AddAnimation(ZAnimationData* Anim);
        void ToggleAnimation(uint8_t Anim, float Time);

        inline uint8_t getCurrentAnimation(){ return CurrentAnimation; };

        //  Handler
        gg::EMessageStatus MHandler_SETPTRS();
        void setVisibility(bool flag);


    private:
        TNodo* DynamicModel;
        SurrealEngine* Surreal;

        CTransform* cTransform;
        uint8_t CurrentAnimation;

};

#endif
