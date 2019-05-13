#ifndef _DEFERRED_SHADING_H
#define _DEFERRED_SHADING_H

#include <cstdint>
#include <Omicron/Shader.hpp>

class DeferredShading{
    friend class Omicron;

        void setnluces(int nluces_F,int nluces_p);

        DeferredShading();
        DeferredShading(const DeferredShading &origin) = delete;
        void operator=(const DeferredShading &origin) = delete;
        ~DeferredShading();

        void init(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT);
        void Bind_G_Buffer();
        void Bind_D_Shader();
        void DrawQuad();
        void DrawPostProcessing();

        Shader* DEFERRED_SHADER;
        Shader* POSTPROCESSING_SHADER;
        unsigned char * buffer;


        unsigned int G_BUFFER, POST_BUFFER;
        unsigned int ubo;
        unsigned int block_index;
        unsigned int binding_point_index;
        unsigned int gPosition, gNormal, gDiffuseSpec, gVelocity, gRender;
        unsigned int G_DepthBuffer;

        unsigned int QUAD;
        unsigned int QUAD_POS_UV;


};

#endif
