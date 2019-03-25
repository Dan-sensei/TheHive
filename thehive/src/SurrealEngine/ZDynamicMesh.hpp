#ifndef ZDYNAMICMESH_H
#define ZDYNAMICMESH_H

#include "ZMaterial.hpp"
#include "ZAnimationData.hpp"
#include "TEntidad.hpp"

class ZDynamicMesh : public TEntidad {
    public:
        ZDynamicMesh();
        ZDynamicMesh(const ZDynamicMesh &orig);
        virtual ~ZDynamicMesh();

        void assignMaterial(ZMaterial* material_);
        void SwitchAnimation(uint8_t Animation, float TimeToComplete);
        void AddAnimation(ZAnimationData* Anim);

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Clock DeltaTime;
        std::vector<ZAnimationData*> Animations;
        Shader* shader;
        ZMaterial* zmat;
        uint8_t CurrentAnimation;
};

#endif
