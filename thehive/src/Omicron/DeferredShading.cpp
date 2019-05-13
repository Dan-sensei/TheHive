#include "DeferredShading.hpp"

#include <GL/glew.h>
#include <Singleton.hpp>
#include <iostream>
#include <Omicron/AssetManager.hpp>
#include <Omicron/TLuz.hpp>

#define tamanyo 1024
#define Nfocales   32
#define Npuntuales   36


struct LUZF
{
    LUZF(){
    }
    LUZF(float x,float y,float z,float x2,float y2,float z2){
        pos[0]=x;
        pos[1]=y;
        pos[2]=z;

        //posfoco[0]=x2;
        //posfoco[1]=y2;
        //posfoco[2]=z2;

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
    glDeleteRenderbuffers(1, &G_DepthBuffer);
};
void DeferredShading::setnluces(int nluces_F,int nluces_p){
    *((float *)(buffer + Nfocales)) = nluces_F;
    *((float *)(buffer + Npuntuales)) = nluces_p;
}
void DeferredShading::init(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT){

    DEFERRED_SHADER = Singleton<AssetManager>::Instance()->getShader("DEFERRED");
    POSTPROCESSING_SHADER = Singleton<AssetManager>::Instance()->getShader("PostProcessing");
    ///UBO ligth
    block_index=DEFERRED_SHADER->getUniformBlockLocation("light");

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


    //int tamanyo=2048;
    buffer = (unsigned char *)malloc(tamanyo);
    TLuz::buffer=buffer;

    //dir
    //0
    ((float*)(buffer + uniformOffsets[0]))[0] = 0.0f;
    ((float*)(buffer + uniformOffsets[0]))[1] = 1.0f;
    ((float*)(buffer + uniformOffsets[0]))[2] = 0.0f;
    //color
    //16
    ((float*)(buffer + uniformOffsets[1]))[0] = 1.0f;
    ((float*)(buffer + uniformOffsets[1]))[1] = 1.0f;
    ((float*)(buffer + uniformOffsets[1]))[2] = 1.0f;

    //ints dire
    //28
    *((float *)(buffer + uniformOffsets[2])) = 0.1f;
    //numero de luces focales actvas
    //32
    *((float *)(buffer + uniformOffsets[3])) = 8;
    //numero de luces puntuales actvas
    //36
    *((float *)(buffer + uniformOffsets[4])) = 8;



    LUZF lucesf[]={
        //LUZF(153.039,   12,     -91.6788,   153.039,    4.245,  -91.6788),
        LUZF(125.788,   4.82238,     -39.5693,   153.039,    4.245,  -91.6788),
        LUZF(103.334,   12,     -87.42,     103.334,    4.245,  -87.42),
        LUZF(185.485,   12,     -52.2665,   185.485,    4.245,  -52.2665),
        LUZF(184.759,   12,     -41.7255,   184.759,    4.245,  -41.7255),

        //LUZF(20,   8.5,    -50.5481,   200.178,    4.245,  -50.5481),
        LUZF(200.178,   8.5,    -50.5481,   200.178,    4.245,  -50.5481),
        LUZF(221.009,   8.5,    -53.6585,   221.009,    4.245,  -53.6585),
        LUZF(242.202,   8.5,    -56.456,    242.202,    4.245,  -56.456),
        LUZF(267.738,   8.5,    -51.9228,   267.738,    4.245,  -51.9228)
    };
    uint8_t nluces=8;
    LUZF aux;
    unsigned int offset = uniformOffsets[5];
    unsigned int offset2 = uniformOffsets[6];
    unsigned int offset3 = uniformOffsets[7];
    unsigned int offset4 = uniformOffsets[8];
    std::cout << "#define Nfocales   " <<uniformOffsets[3]<< '\n';
    std::cout << "#define Npuntuales   " <<uniformOffsets[4]<< '\n';
    std::cout << "Luz dirigida" << '\n';
    for (size_t i = 5; i < 9; i++) {
        std::cout << "#define U"<<i<<"    " <<uniformOffsets[i]<< '\n';
        std::cout << "#define S"<<i<<"    " <<arrayStrides[i]<< '\n';
    }

    for (uint8_t n = 0; n < nluces; n++)
    {
        aux=lucesf[n];

        ((float*)(buffer + offset))[0] = aux.pos[0];
        ((float*)(buffer + offset))[1] = aux.pos[1];
        ((float*)(buffer + offset))[2] = aux.pos[2];
        offset += arrayStrides[5];

        ((float*)(buffer + offset2))[0] = aux.posfoco[0];
        ((float*)(buffer + offset2))[1] = aux.posfoco[1];
        ((float*)(buffer + offset2))[2] = aux.posfoco[2];
        offset2 += arrayStrides[6];

        ((float*)(buffer + offset3))[0] = aux.color[0];
        ((float*)(buffer + offset3))[1] = aux.color[1];
        ((float*)(buffer + offset3))[2] = aux.color[2];
        offset3 += arrayStrides[7];

        *((float *)(buffer + offset4)) = aux.intensidad;
        offset4 += arrayStrides[8];
    }
    //std::cout << "final" <<offset4<< '\n';
    std::cout << "Luz puntuales" << '\n';
    for (size_t i = 9; i < 12; i++) {
        std::cout << "#define U"<<i<<"    " <<uniformOffsets[i]<< '\n';
        std::cout << "#define S"<<i<<"    " <<arrayStrides[i]<< '\n';
    }

    std::cout << "/* max */" << uniformOffsets[11]+arrayStrides[11]*9<<'\n';
    offset = uniformOffsets[9];
    offset2 = uniformOffsets[10];
    offset3 = uniformOffsets[11];
    //std::cout << "Luz puntuales" << '\n';
    //std::cout << "offset" <<offset<< '\n';
    //std::cout << "offset2" <<offset2<< '\n';
    //std::cout << "offset3" <<offset3<< '\n';
    /*

    for (int n = 0; n < nluces; n++)
    {
        aux=lucesf[n];

        ((float*)(buffer +offset))[0] = aux.pos[0];
        ((float*)(buffer +offset))[1] = aux.pos[1];
        ((float*)(buffer +offset))[2] = aux.pos[2];
        offset += arrayStrides[9];

        ((float*)(buffer +offset2))[0] = aux.posfoco[0];
        ((float*)(buffer +offset2))[1] = aux.posfoco[1];
        ((float*)(buffer +offset2))[2] = aux.posfoco[2];
        offset2 += arrayStrides[10];

        *((float *)(buffer + offset3)) = aux.intensidad;
        offset3 += arrayStrides[11];

    }
    */


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
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_R16F, SCREEN_WIDTH, SCREEN_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

        // G-BUFFER DE NORMALES
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8_SNORM, SCREEN_WIDTH, SCREEN_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

        // G-BUFFER DE TEXTURAS DIFUSA Y ESPECULAR
        glBindTexture(GL_TEXTURE_2D, gDiffuseSpec);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gDiffuseSpec, 0);

        // G-BUFFER DE VELOCIDAD PARA EL MOTION BLUR
        glBindTexture(GL_TEXTURE_2D, gVelocity);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RG16F, SCREEN_WIDTH, SCREEN_HEIGHT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gVelocity, 0);

        unsigned int attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glDrawBuffers(4, attachments);

        // DEPTH BUFFER PARA NUESTRO G-BUFFER
        glBindRenderbuffer(GL_RENDERBUFFER, G_DepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, SCREEN_WIDTH, SCREEN_HEIGHT);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, G_DepthBuffer);

    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }


    glCreateFramebuffers(1, &POST_BUFFER);
    glGenTextures(1, &gRender);
    glBindFramebuffer(GL_FRAMEBUFFER, POST_BUFFER);

        // POST-BUFFER FINAL
        glBindTexture(GL_TEXTURE_2D, gRender);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT);
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
    //((float*)(buffer ))[1] = 150.0f;

    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, tamanyo, buffer, GL_DYNAMIC_DRAW);
    // no hace falta esto
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
    //glBindVertexArray(0);
}
