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
        void SwitchAnimation(uint8_t Animation, float TimeBetweenKeyframes);
        void AddAnimation(ZAnimationData* Anim);

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Clock DeltaTime;
        
        std::vector<ZAnimationData*> Animations;
        Shader* shader;
        ZMaterial* zmat;

        double Timer;
        float TimeBetweenAnimations;

        uint8_t CurrentAnimation;
        uint8_t CurrentFrame;
        uint8_t NextFrame;
        uint8_t NFrames;


};

#endif
