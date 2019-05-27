#include "ZDynamicMesh.hpp"
#include <ShaderUniformMapping.hpp>
#include <iostream>

ZDynamicMesh::ZDynamicMesh()
:shader(nullptr), CurrentUpd(&ZDynamicMesh::checkAnimationComplete), LastPosition(), CurrentPosition(), Timer(0), TimeBetweenAnimations(0),
 AngleAccumulator(0), StepDistance(2.f), NeedsToComplete(false), animationPlayed(false), CurrentAnimation(0), CurrentFrame(0), NextFrame(0), NFrames(0)
{
    Animations.reserve(5);
    zmat = nullptr;
    MVP = glm::mat4();
}

ZDynamicMesh::ZDynamicMesh(const ZDynamicMesh &orig)
:Animations(orig.Animations), shader(orig.shader)
{
    zmat = orig.zmat;
}

ZDynamicMesh::~ZDynamicMesh(){}
//
// void ZDynamicMesh::assignMaterial(ZMaterial* material_){
//     zmat = material_;
//     shader = zmat->getShader();
// }

bool ZDynamicMesh::SwitchAnimation(uint8_t Animation, float TimeBetweenKeyframes, bool _NeedsToComplete, bool Auto) {

    if(NeedsToComplete && !animationPlayed) return false;
    CurrentAnimation = Animation;
    DeltaTime.Restart();
    TimeBetweenAnimations = TimeBetweenKeyframes;
    Timer = 0;
    CurrentFrame = 0;
    NextFrame = 1;
    animationPlayed = false;
    NFrames = Animations[Animation]->Keyframes.size();
    NeedsToComplete = _NeedsToComplete;
    CurrentUpd = Auto ? &ZDynamicMesh::checkAnimationComplete : &ZDynamicMesh::Manual;

    return true;
}

void ZDynamicMesh::setPosForStep(const glm::vec2 &P){
    CurrentPosition = P;
}
void ZDynamicMesh::setStepDistance(float D){
    StepDistance = D;
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
    glUniformMatrix4fv(12,1,GL_FALSE,&MVP[0][0]);

    MVP = projMatrix * viewMatrix * modelMatrix;
    glUniformMatrix4fv(_U_MVP,1,GL_FALSE,&MVP[0][0]);

    (this->*CurrentUpd)();
}

void ZDynamicMesh::checkAnimationComplete(){

    Timer += DeltaTime.Restart().Seconds();
    if(Timer > TimeBetweenAnimations){
        CurrentFrame = (CurrentFrame + 1) % NFrames;
        NextFrame = (CurrentFrame + 1) % NFrames;
        Timer -= TimeBetweenAnimations;
        if(CurrentFrame == 0) {
            animationPlayed = true;
            CurrentUpd = &ZDynamicMesh::Auto;
        }
    }
    glUniform1f(_U_BLEND_FACTOR, Timer/TimeBetweenAnimations);

    Animations[CurrentAnimation]->draw(CurrentFrame, NextFrame);
}

void ZDynamicMesh::Auto(){
    Timer += DeltaTime.Restart().Seconds();
    if(Timer > TimeBetweenAnimations){
        CurrentFrame = (CurrentFrame + 1) % NFrames;
        NextFrame = (CurrentFrame + 1) % NFrames;
        Timer -= TimeBetweenAnimations;
    }

    glUniform1f(_U_BLEND_FACTOR, Timer/TimeBetweenAnimations);

    Animations[CurrentAnimation]->draw(CurrentFrame, NextFrame);
}

void ZDynamicMesh::Manual() {
    float dist = glm::length(LastPosition - CurrentPosition);
    // float turnAngle = (dist / (2 * 3.14159265359f * 0.75f)) * 360.f;
    float turnAngle = dist * 1.2f;

    AngleAccumulator += turnAngle;

    if (AngleAccumulator > StepDistance){
        AngleAccumulator = 0;
        CurrentFrame = (CurrentFrame + 1) % NFrames;
        NextFrame = (CurrentFrame + 1) % NFrames;
    }

    float Factor = AngleAccumulator/StepDistance;
    Factor = (Factor/NFrames) / (1.f/NFrames);

    glUniform1f(_U_BLEND_FACTOR, Factor);
    Animations[CurrentAnimation]->draw(CurrentFrame, NextFrame);

    LastPosition = CurrentPosition;
}

void ZDynamicMesh::endDraw(){}
