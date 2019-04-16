#ifndef ZDYNAMICMESH_H
#define ZDYNAMICMESH_H

#include <Omicron/ZMaterial.hpp>
#include "ZAnimationData.hpp"
#include <Omicron/CORE/TEntidad.hpp>
#include <Omicron/ZMESHES/ZMesh.hpp>

class ZDynamicMesh : public ZMesh {
    public:
        ZDynamicMesh();
        ZDynamicMesh(const ZDynamicMesh &orig);
        virtual ~ZDynamicMesh();

        void SwitchAnimation(uint8_t Animation, float TimeBetweenKeyframes);
        void AddAnimation(ZAnimationData* Anim);

        inline bool getAnimationPlayed(){ return animationPlayed; };

        virtual void beginDraw();
        virtual void endDraw();

    private:
        gg::Clock DeltaTime;

        std::vector<ZAnimationData*> Animations;
        Shader* shader;

        double Timer;
        float TimeBetweenAnimations;

        bool animationPlayed;

        uint8_t CurrentAnimation;
        uint8_t CurrentFrame;
        uint8_t NextFrame;
        uint8_t NFrames;


};

#endif
