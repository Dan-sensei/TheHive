#include "ZDynamicMesh.hpp"
#include <ShaderUniformMapping.hpp>
#include <iostream>

ZDynamicMesh::ZDynamicMesh()
:CurrentAnimation(0), shader(nullptr), zmat(nullptr), CurrentFrame(0), NextFrame(0), NFrames(0)
{
    Animations.reserve(5);
}

ZDynamicMesh::ZDynamicMesh(const ZDynamicMesh &orig)
:Animations(orig.Animations), shader(orig.shader), zmat(orig.zmat)
{}

ZDynamicMesh::~ZDynamicMesh(){}

void ZDynamicMesh::assignMaterial(ZMaterial* material_){
    zmat = material_;
    shader = zmat->getShader();
}

void ZDynamicMesh::SwitchAnimation(uint8_t Animation, float TimeBetweenKeyframes){
    CurrentAnimation = Animation;
    DeltaTime.Restart();
    TimeBetweenAnimations = TimeBetweenKeyframes;
    Timer = 0;
    CurrentFrame = 0;
    NFrames = Animations[Animation]->Keyframes.size() - 1;
}

void ZDynamicMesh::AddAnimation(ZAnimationData* Anim){
    Animations.push_back(Anim);
}

// Se quedan vacios
void ZDynamicMesh::beginDraw(){
    zmat->Bind();

    glm::mat4 MV = viewMatrix*modelMatrix;

    // MODELO
    glUniformMatrix4fv(9,1,GL_FALSE,&MV[0][0]);

    // NORMAL_MATRIX
    glm::mat3 VP = glm::transpose(glm::inverse(glm::mat3(MV)));
    glUniformMatrix3fv(_U_MODEL,1,GL_FALSE,&VP[0][0]);

    // MODELO*VISTA*PERSPECTIVA
    glm::mat4 MVP_L = projMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(_U_MVP,1,GL_FALSE,&MVP_L[0][0]);

    Timer += DeltaTime.Restart().Seconds();
    if(Timer > TimeBetweenAnimations){
        CurrentFrame = (CurrentFrame + 1) % NFrames;
        NextFrame = (CurrentFrame + 1) % NFrames;
        Timer -= TimeBetweenAnimations;
    }

    glUniform1f(_U_BLEND_FACTOR, Timer/TimeBetweenAnimations);

    Animations[CurrentAnimation]->draw(CurrentFrame, NextFrame);
}

void ZDynamicMesh::endDraw(){}
