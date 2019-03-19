#include "ZAnimator.hpp"

ZAnimator::ZAnimator()
:CurrentAnimation(0), shader(nullptr), zmat(nullptr)
{
    Animations.reserve(5);
}

ZAnimator::ZAnimator(const ZAnimator &orig)
:Animations(orig.Animations), shader(orig.shader), zmat(orig.zmat)
{}

ZAnimator::~ZAnimator(){}

void ZAnimator::assignMaterial(ZMaterial* material_){
    zmat = material_;
}

void ZAnimator::SwitchAnimation(uint8_t Animation){
    CurrentAnimation = Animation;
    DeltaTime.Restart();
}

// Se quedan vacios
void ZAnimator::beginDraw(const uint8_t &T_ID){
    if(T_ID == 2){

        zmat->Bind();

        // MODELO
        GLuint M = shader->getUniformLocation("M");
        glUniformMatrix4fv(M,1,GL_FALSE,&modelMatrix[0][0]);

        // MODELO*VISTA*PERSPECTIVA
        glm::mat4 MVP_L = projMatrix * viewMatrix * modelMatrix;
        GLuint MVP = shader->getUniformLocation("MVP");
        glUniformMatrix4fv(MVP,1,GL_FALSE,&MVP_L[0][0]);

        Animations[CurrentAnimation]->draw(DeltaTime.Restart().Seconds());
    }
}

void ZAnimator::endDraw(const uint8_t &T_ID){

}
