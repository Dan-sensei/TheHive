#include "ZAnimationData.hpp"
#include "AssetManager.hpp"

ZAnimationData::ZAnimationData()
:IndexSize(0), NFrames(0), CurrentFrame(0), NextFrame(0), Timer(0)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        glEnableVertexAttribArray(7);
        glEnableVertexAttribArray(8);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(2, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(3, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(4, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(5, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(6, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(7, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(8, 3, GL_FLOAT, false, 12);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 1);
        glVertexAttribBinding(3, 2);
        glVertexAttribBinding(4, 2);
        glVertexAttribBinding(5, 3);
        glVertexAttribBinding(6, 3);
        glVertexAttribBinding(7, 4);
        glVertexAttribBinding(8, 4);

    glBindVertexArray(0);
    Keyframes.reserve(5);
}

ZAnimationData::ZAnimationData(const ZAnimationData &orig)
:Keyframes(orig.Keyframes), IndexSize(orig.IndexSize), NFrames(orig.NFrames),
CurrentFrame(orig.CurrentFrame), NextFrame(orig.NextFrame), Timer(orig.Timer){}

ZAnimationData::~ZAnimationData(){}

void ZAnimationData::addKeyframe(const std::string &PathToKeyframeModel){
    Keyframes.emplace_back(Singleton<AssetManager>::Instance()->getMeshData(PathToKeyframeModel));

    if(!IndexSize){
        IndexSize = Keyframes.back()->IndexSize;
        glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  Keyframes.back()->IndexBuffer);
        glBindVertexArray(0);
    }

    NFrames = Keyframes.size();
}

void ZAnimationData::setAnimationTime(float _Time){
    TimeBetweenAnimations = _Time/NFrames;
    Timer = 0;
    CurrentFrame = 0;
}

void ZAnimationData::draw(float DeltaTime){
    if(Timer > TimeBetweenAnimations){
        CurrentFrame %= NFrames;
        NextFrame = (CurrentFrame + 1) % NFrames;
    }

    glBindVertexArray(VAO);
        glBindVertexBuffer(0, Keyframes[CurrentFrame]->VBOs[0], 0, 24);
        glBindVertexBuffer(1, Keyframes[CurrentFrame]->VBOs[1], 0, 8);
        glBindVertexBuffer(2, Keyframes[CurrentFrame]->VBOs[2], 0, 24);
        glBindVertexBuffer(3, Keyframes[NextFrame]->VBOs[0], 0, 24);
        glBindVertexBuffer(4, Keyframes[NextFrame]->VBOs[1], 0, 24);

        glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);

    Timer += DeltaTime;
}
