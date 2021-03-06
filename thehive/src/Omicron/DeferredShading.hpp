#ifndef _DEFERRED_SHADING_H
#define _DEFERRED_SHADING_H

#include <cstdint>
#include <Omicron/Shader.hpp>
#include <glm/glm.hpp>

class DeferredShading{
    friend class Omicron;

        DeferredShading();
        DeferredShading(const DeferredShading &origin) = delete;
        void operator=(const DeferredShading &origin) = delete;
        ~DeferredShading();

        void init(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT, uint16_t _SCREEN_WIDTH, uint16_t _SCREEN_HEIGHT);
        void Bind_G_Buffer();
        void Bind_D_Shader();
        void DrawQuad();
        void DrawPostProcessing();

        void setGlobalIlumination(float Intensity);
        void setnluces(int nluces_F, int nluces_p);
        void setDirLuz(glm::vec3 dir,glm::vec3 color,float inten);
        void info();

        void resizeFrameBuffers(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT);

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


        int WIDTH, HEIGHT;
        int SCREEN_WIDTH, SCREEN_HEIGHT;

        void createFramebuffers(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT);
};

#endif
