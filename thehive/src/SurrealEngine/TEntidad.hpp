#ifndef TENTIDAD_H
#define TENTIDAD_H

#include <stack>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <cstdint>

class TEntidad {
    public:
        virtual ~TEntidad()         = 0;
        virtual void beginDraw(uint8_t)    = 0;
        virtual void endDraw()      = 0;

    protected:
        static std::stack<glm::mat4> matrixStack;
        static glm::mat4 modelMatrix;
};

#endif
