#ifndef ZANIMATIONDATA_H
#define ZANIMATIONDATA_H

#include "ZMeshData.hpp"
#include <vector>
#include "Clock.hpp"

class ZAnimationData {
    public:
        ZAnimationData();
        ZAnimationData(const ZAnimationData &orig);
        ~ZAnimationData();

        void addKeyframe(const std::string &PathToKeyframeModel);
        void setAnimationTime(float _Time);
        void draw(float Deltatime);

    private:
        std::vector<ZMeshData*> Keyframes;
        float Timer;
        float TimeBetweenAnimations;
        unsigned int VAO;
        unsigned int IndexSize;
        uint8_t NFrames;
        uint8_t CurrentFrame;
        uint8_t NextFrame;
};

#endif
