#ifndef ZANIMATIONDATA_H
#define ZANIMATIONDATA_H

#include <Omicron/ZMESHES/ZMeshData.hpp>
#include <vector>
#include <Omicron/Clock.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ZAnimationData {
    friend class ZDynamicMesh;
    public:
        ZAnimationData();
        ZAnimationData(const ZAnimationData &orig);
        ~ZAnimationData();

        void addKeyframe(const std::string &PathToKeyframeModel);
        void draw(uint8_t CurrentFrame, uint8_t NextFrame);

    private:
        std::vector<ZMeshData*> Keyframes;
        unsigned int VAO;
        unsigned int IndexSize;

};

#endif
