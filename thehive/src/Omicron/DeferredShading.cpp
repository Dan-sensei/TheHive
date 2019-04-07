#include "DeferredShading.hpp"

#include <GL/glew.h>
#include <Singleton.hpp>
#include <Omicron/AssetManager.hpp>

DeferredShading::DeferredShading(){}

DeferredShading::~DeferredShading(){
    glDeleteVertexArrays(1, &QUAD);
    glDeleteBuffers(1, &QUAD_POS_UV);

    glDeleteFramebuffers(1, &G_BUFFER);
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gDiffuseSpec);
    glDeleteRenderbuffers(1, &G_DepthBuffer);
};

void DeferredShading::init(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT){

    DEFERRED_SHADER = Singleton<AssetManager>::Instance()->getShader("DEFERRED");

    float RENDER_QUAD[] = {
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &QUAD);

        glGenBuffers(1, &QUAD_POS_UV);
        glBindVertexArray(QUAD);
        glBindBuffer(GL_ARRAY_BUFFER, QUAD_POS_UV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD), &RENDER_QUAD, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 2, GL_FLOAT, false, 12);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);

        glBindVertexBuffer(0, QUAD_POS_UV, 0, 20);

    glBindVertexArray(0);

    glCreateFramebuffers(1, &G_BUFFER);
    glGenTextures(1, &gPosition);
    glGenTextures(1, &gNormal);
    glGenTextures(1, &gDiffuseSpec);
    glGenRenderbuffers(1, &G_DepthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, G_BUFFER);

        // G-BUFFER DE POSICIONES
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, SCREEN_WIDTH, SCREEN_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

        // G-BUFFER DE NORMALES
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA16F, SCREEN_WIDTH, SCREEN_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

        // G-BUFFER DE TEXTURAS DIFUSA Y ESPECULAR
        glBindTexture(GL_TEXTURE_2D, gDiffuseSpec);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gDiffuseSpec, 0);

        unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
        glDrawBuffers(3, attachments);

        // DEPTH BUFFER PARA NUESTRO G-BUFFER
        glBindRenderbuffer(GL_RENDERBUFFER, G_DepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, G_DepthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeferredShading::Bind_G_Buffer(){
    glBindFramebuffer(GL_FRAMEBUFFER, G_BUFFER);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DeferredShading::Bind_D_Shader(){
    DEFERRED_SHADER->Bind();
}

void DeferredShading::DrawQuad(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DEFERRED_SHADER->Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glUniform1i(5, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glUniform1i(6, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gDiffuseSpec);
    glUniform1i(7, 2);

    glBindVertexArray(QUAD);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
