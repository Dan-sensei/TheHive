#include "ZAnimationData.hpp"
#include <Omicron/AssetManager.hpp>
#include <iostream>
#include <Singleton.hpp>
#include <ShaderUniformMapping.hpp>

ZAnimationData::ZAnimationData()
:IndexSize(0)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);   // UV
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        glEnableVertexAttribArray(7);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(2, 2, GL_FLOAT, false, 24);
        glVertexAttribFormat(3, 3, GL_FLOAT, false, 32);
        glVertexAttribFormat(5, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(6, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(7, 3, GL_FLOAT, false, 32);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 0);
        glVertexAttribBinding(3, 0);
        glVertexAttribBinding(5, 1);
        glVertexAttribBinding(6, 1);
        glVertexAttribBinding(7, 1);

    glBindVertexArray(0);
    Keyframes.reserve(5);
}

ZAnimationData::ZAnimationData(const ZAnimationData &orig)
:Keyframes(orig.Keyframes), IndexSize(orig.IndexSize){}

ZAnimationData::~ZAnimationData(){}

void ZAnimationData::addKeyframe(const std::string &PathToKeyframeModel){
    Keyframes.emplace_back(Singleton<AssetManager>::Instance()->getMeshData(PathToKeyframeModel));

    if(!IndexSize){
        IndexSize = Keyframes.back()->IndexSize;
        glBindVertexArray(VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,  Keyframes.back()->IndexBuffer);
        glBindVertexArray(0);
    }
}

void ZAnimationData::draw(uint8_t CurrentFrame, uint8_t NextFrame){
    glBindVertexArray(VAO);
        glBindVertexBuffer(0, Keyframes[CurrentFrame]->VBO, 0, 44);
        glBindVertexBuffer(1, Keyframes[NextFrame]->VBO, 0, 44);

        glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}
