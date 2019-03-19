#ifndef ZANIMATOR_H
#define ZANIMATOR_H

#include "ZMaterial.hpp"
#include "ZAnimationData.hpp"
#include "TEntidad.hpp"

class ZAnimator : public TEntidad {
    public:
        ZAnimator();
        ZAnimator(const ZAnimator &orig);
        virtual ~ZAnimator();

        void assignMaterial(ZMaterial* material_);
        void SwitchAnimation(uint8_t Animation);

        virtual void beginDraw(const uint8_t&);
        virtual void endDraw(const uint8_t&);

    private:
        gg::Clock DeltaTime;
        std::vector<ZAnimationData*> Animations;
        Shader* shader;
        ZMaterial* zmat;
        uint8_t CurrentAnimation;
};

#endif
