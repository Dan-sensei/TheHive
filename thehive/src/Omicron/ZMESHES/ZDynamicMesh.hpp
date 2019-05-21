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

        void SwitchAnimation(uint8_t Animation, float TimeBetweenKeyframes, bool Auto);
        void AddAnimation(ZAnimationData* Anim);
        void setPosForStep(const glm::vec2 &P);
        void setStepDistance(float D);

        inline bool getAnimationPlayed(){ return animationPlayed; };

        virtual void beginDraw();
        virtual void endDraw();

    private:
        void Auto();
        void Manual();

        gg::Clock DeltaTime;
        std::vector<ZAnimationData*> Animations;
        Shader* shader;

        void (ZDynamicMesh::*CurrentUpd)();

        glm::vec2 LastPosition;
        glm::vec2 CurrentPosition;
        double Timer;
        float TimeBetweenAnimations;
        float AngleAccumulator;
        float StepDistance;

        bool animationPlayed;

        uint8_t CurrentAnimation;
        uint8_t CurrentFrame;
        uint8_t NextFrame;
        uint8_t NFrames;


};

#endif
