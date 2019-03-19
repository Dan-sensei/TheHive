#ifndef ZANIMATIONDATA_H
#define ZANIMATIONDATA_H

#include "ZMeshData.hpp"
#include <vector>

class ZAnimationData {
    public:
        ZAnimationData();
        ZAnimationData(const ZAnimationData &orig);
        ~ZAnimationData();

        void addKeyframe(const std::string &PathToKeyframeModel);
    private:
        std::vector<ZMeshData*> Keyframes;
};

#endif
