#include "ZDynamicMesh.hpp"

ZDynamicMesh::ZDynamicMesh()
:CurrentAnimation(0), shader(nullptr), zmat(nullptr)
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

void ZDynamicMesh::SwitchAnimation(uint8_t Animation, float TimeToComplete){
    CurrentAnimation = Animation;
    DeltaTime.Restart();
    Animations[Animation]->setAnimationTime(TimeToComplete);
}

void ZDynamicMesh::AddAnimation(ZAnimationData* Anim){
    Animations.push_back(Anim);
}

// Se quedan vacios
void ZDynamicMesh::beginDraw(){
    zmat->Bind();

    // MODELO
    GLuint M = shader->getUniformLocation("M");
    glUniformMatrix4fv(M,1,GL_FALSE,&modelMatrix[0][0]);

    // MODELO*VISTA*PERSPECTIVA
    glm::mat4 MVP_L = projMatrix * viewMatrix * modelMatrix;
    GLuint MVP = shader->getUniformLocation("MVP");
    glUniformMatrix4fv(MVP,1,GL_FALSE,&MVP_L[0][0]);

    unsigned int TIME = shader->getUniformLocation("TweenFactor");
    Animations[CurrentAnimation]->draw(DeltaTime.Restart().Seconds(), TIME);
}

void ZDynamicMesh::endDraw(){}
