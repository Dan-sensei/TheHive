#ifndef _DEFERRED_SHADING_H
#define _DEFERRED_SHADING_H

#include <cstdint>
#include <Omicron/Shader.hpp>

class DeferredShading{
    friend class Omicron;

        DeferredShading();
        DeferredShading(const DeferredShading &origin) = delete;
        void operator=(const DeferredShading &origin) = delete;
        ~DeferredShading();

        void init(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT);
        void Bind_G_Buffer();
        void Bind_D_Shader();
        void DrawQuad();

        Shader* DEFERRED_SHADER;

        unsigned int G_BUFFER;
        unsigned int gPosition, gNormal, gDiffuseSpec;
        unsigned int G_DepthBuffer;

        unsigned int QUAD;
        unsigned int QUAD_POS_UV;


};

#endif
