#include "DeferredShading.hpp"

#include <GL/glew.h>
#include <Singleton.hpp>
#include <iostream>
#include <Omicron/AssetManager.hpp>
#include <Omicron/LIGHTS/TLuz.hpp>

#define tamanyo 2048
#define Ldirec   0
#define Lcolor  16
#define Lint   28
#define Nfocales   32
#define Npuntuales   36

#define DIRECTIONAL_LIGHT_FACTOR 0.5

struct LUZF
{
    LUZF(){
    }
    LUZF(float x,float y,float z,float x2,float y2,float z2){
        pos[0]=x;
        pos[1]=y;
        pos[2]=z;;

        posfoco[0]=0;
        posfoco[1]=-1;
        posfoco[2]=0;

        color[0]=1;
        color[1]=1;
        color[2]=1;

        intensidad=150;
    }
  float pos[3];
  float posfoco[3];
  float color[3];
  float intensidad;
};

void DeferredShading::setnluces(int nluces_F,int nluces_p){
    *((float *)(buffer + Nfocales)) = nluces_F;
    *((float *)(buffer + Npuntuales)) = nluces_p;
}

void DeferredShading::setDirLuz(glm::vec3 dir,glm::vec3 color,float inten){
    ((float*)(buffer + Ldirec))[0] = dir.x;
    ((float*)(buffer + Ldirec))[1] = dir.y;
    ((float*)(buffer + Ldirec))[2] = dir.z;

    ((float*)(buffer + Lcolor))[0] = color.x;
    ((float*)(buffer + Lcolor))[1] = color.y;
    ((float*)(buffer + Lcolor))[2] = color.z;
    *((float *)(buffer + Lint)) = inten;
}




void DeferredShading::info(){

    int tam=12;
    static const GLchar * uniformNames[12] =
    {
        "light.dirluzD",
        "light.colorluzD",
        "light.intluzD",
        "light.NNlucesF",
        "light.NNlucesP",
        "light.posluzF",
        "light.posfocoluzF",
        "light.colorluzF",
        "light.intluzF",
        "light.posluzP",
        "light.colorluzP",
        "light.intluzP"
    };
    GLuint uniformIndices[tam];
    glGetUniformIndices(DEFERRED_SHADER->getID(), tam, uniformNames, uniformIndices);
    GLint uniformOffsets[tam];
    GLint arrayStrides[tam];
    GLint matrixStrides[tam];
    glGetActiveUniformsiv(DEFERRED_SHADER->getID(), tam, uniformIndices,
    GL_UNIFORM_OFFSET, uniformOffsets);
    glGetActiveUniformsiv(DEFERRED_SHADER->getID(), tam, uniformIndices,
    GL_UNIFORM_ARRAY_STRIDE, arrayStrides);
    glGetActiveUniformsiv(DEFERRED_SHADER->getID(), tam, uniformIndices,
    GL_UNIFORM_MATRIX_STRIDE, matrixStrides);

    std::cout << "#define Ldirec     " <<uniformOffsets[0]<< '\n';
    std::cout << "#define Lcolor     " <<uniformOffsets[1]<< '\n';
    std::cout << "#define Lint       " <<uniformOffsets[2]<< '\n';
    std::cout << "#define Nfocales   " <<uniformOffsets[3]<< '\n';
    std::cout << "#define Npuntuales " <<uniformOffsets[4]<< '\n';
    std::cout << "Luz dirigida" << '\n';
    for (size_t i = 5; i < 9; i++) {
        std::cout << "#define U"<<i<<"    " <<uniformOffsets[i]<< '\n';
        std::cout << "#define S"<<i<<"    " <<arrayStrides[i]<< '\n';
    }


    //std::cout << "final" <<offset4<< '\n';
    std::cout << "Luz puntuales" << '\n';
    for (size_t i = 9; i < 12; i++) {
        std::cout << "#define U"<<i<<"    " <<uniformOffsets[i]<< '\n';
        std::cout << "#define S"<<i<<"    " <<arrayStrides[i]<< '\n';
    }

    std::cout << "MAX MEMORY NEEDED" << uniformOffsets[11]+arrayStrides[11]*9<<'\n';

}

DeferredShading::DeferredShading(){}

DeferredShading::~DeferredShading(){
    glDeleteVertexArrays(1, &QUAD);
    glDeleteBuffers(1, &QUAD_POS_UV);
    glDeleteBuffers(1, &ubo);
    free(buffer);

    glDeleteFramebuffers(1, &G_BUFFER);
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gDiffuseSpec);
    glDeleteTextures(1, &gVelocity);
    glDeleteRenderbuffers(1, &G_DepthBuffer);

    glDeleteFramebuffers(1, &POST_BUFFER);
    glDeleteTextures(1, &gRender);
}

void DeferredShading::resizeFrameBuffers(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT){
    glDeleteFramebuffers(1, &G_BUFFER);
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gDiffuseSpec);
    glDeleteTextures(1, &gVelocity);
    glDeleteRenderbuffers(1, &G_DepthBuffer);

    glDeleteFramebuffers(1, &POST_BUFFER);
    glDeleteTextures(1, &gRender);

    createFramebuffers(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
}

void DeferredShading::init(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT, uint16_t _SCREEN_WIDTH, uint16_t _SCREEN_HEIGHT){


    SCREEN_WIDTH = _SCREEN_WIDTH;
    SCREEN_HEIGHT = _SCREEN_HEIGHT;

    DEFERRED_SHADER = Singleton<AssetManager>::Instance()->getShader("DEFERRED");
    POSTPROCESSING_SHADER = Singleton<AssetManager>::Instance()->getShader("PostProcessing");
    ///UBO ligth

    block_index=DEFERRED_SHADER->getUniformBlockLocation("light");
    buffer = (unsigned char *)malloc(tamanyo);
    TLuz::buffer=buffer;

    // info();

    setDirLuz(glm::vec3(0,1,0), glm::vec3(1,1,1), DIRECTIONAL_LIGHT_FACTOR);
    setnluces(0,0);


    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, tamanyo, buffer, GL_DYNAMIC_DRAW);
    //glBufferData(GL_UNIFORM_BUFFER, sizeof(luces), &luces, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    binding_point_index=0;
    glUniformBlockBinding(DEFERRED_SHADER->getID(), block_index, binding_point_index);

    //solo si tenemos mas de uno
    glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, ubo);

    /* update
    glBindBuffer(GL_UNIFORM_BUFFER, gbo);
    GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    memcpy(p, &shader_data, sizeof(shader_data))
    glUnmapBuffer(GL_UNIFORM_BUFFER);
    */

    float RENDER_QUAD[] = {
        -1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &QUAD);

        glGenBuffers(1, &QUAD_POS_UV);
        glBindVertexArray(QUAD);
        glBindBuffer(GL_ARRAY_BUFFER, QUAD_POS_UV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD), &RENDER_QUAD, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribFormat(0, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 2, GL_FLOAT, false, 8);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);

        glBindVertexBuffer(0, QUAD_POS_UV, 0, 16);

    glBindVertexArray(0);

    createFramebuffers(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
}

void DeferredShading::createFramebuffers(uint16_t FRAMEBUFFER_WIDTH, uint16_t FRAMEBUFFER_HEIGHT){
    WIDTH = FRAMEBUFFER_WIDTH;
    HEIGHT = FRAMEBUFFER_HEIGHT;
    glCreateFramebuffers(1, &G_BUFFER);
    glGenTextures(1, &gPosition);
    glGenTextures(1, &gNormal);
    glGenTextures(1, &gDiffuseSpec);
    glGenTextures(1, &gVelocity);
    glGenRenderbuffers(1, &G_DepthBuffer);

    {
    glBindFramebuffer(GL_FRAMEBUFFER, G_BUFFER);

        // G-BUFFER DE POSICIONES
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_R16F, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

        // G-BUFFER DE NORMALES
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8_SNORM, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

        // G-BUFFER DE TEXTURAS DIFUSA Y ESPECULAR
        glBindTexture(GL_TEXTURE_2D, gDiffuseSpec);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gDiffuseSpec, 0);

        // G-BUFFER DE VELOCIDAD PARA EL MOTION BLUR
        glBindTexture(GL_TEXTURE_2D, gVelocity);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RG16F, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gVelocity, 0);

        unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glDrawBuffers(4, attachments);

        // DEPTH BUFFER PARA NUESTRO G-BUFFER
        glBindRenderbuffer(GL_RENDERBUFFER, G_DepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, G_DepthBuffer);

    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }


    glCreateFramebuffers(1, &POST_BUFFER);
    glGenTextures(1, &gRender);
    glBindFramebuffer(GL_FRAMEBUFFER, POST_BUFFER);

        // POST-BUFFER FINAL
        glBindTexture(GL_TEXTURE_2D, gRender);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gRender, 0);

        unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, attachments);

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
    glBindFramebuffer(GL_FRAMEBUFFER, POST_BUFFER);
    glClear(GL_COLOR_BUFFER_BIT);

    DEFERRED_SHADER->Bind();

    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, tamanyo, buffer, GL_DYNAMIC_DRAW);
    //glUniformBlockBinding(DEFERRED_SHADER->getID(), block_index, binding_point_index);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gDiffuseSpec);

    glBindVertexArray(QUAD);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //glBindVertexArray(0);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    POSTPROCESSING_SHADER->Bind();
}

void DeferredShading::DrawPostProcessing(){

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gRender);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gVelocity);

    glBindVertexArray(QUAD);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // std::cout << " WIDTH " << WIDTH << '\n';
    // std::cout << "HEIGHT " << HEIGHT << '\n';

    glBindFramebuffer(GL_READ_FRAMEBUFFER, G_BUFFER);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glBindVertexArray(0);
}
