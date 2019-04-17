#include "ZMeshData.hpp"
#include <GL/glew.h>
#include "BinaryParser.hpp"
#include <Omicron/OpenGEnum.hpp>
//#include <iostream>

ZMeshData::ZMeshData()
:VAO(0), IndexSize(0)
{
    glGenVertexArrays(1, &VAO);
    VBOs.reserve(3);
    VBOs.resize(3);
}

ZMeshData::ZMeshData(const ZMeshData &orig)
:VAO(orig.VAO), IndexSize(orig.IndexSize)
{
    VBOs.resize(orig.VBOs.size());
    for(uint16_t i = 0; i < VBOs.size(); ++i){
        VBOs[i] = orig.VBOs[i];
    }
}

ZMeshData::~ZMeshData(){
    uint8_t i = VBOs.size();
    while(i--)  glDeleteBuffers(1, &VBOs[i]);

    glDeleteVertexArrays(1, &VAO);
}

bool ZMeshData::load(const std::string& path){

    glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(2, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(3, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(4, 3, GL_FLOAT, false, 12);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 1);
        glVertexAttribBinding(3, 2);
        glVertexAttribBinding(4, 2);

        glCreateBuffers(1, &VBOs[0]);
        glCreateBuffers(1, &VBOs[1]);
        glCreateBuffers(1, &VBOs[2]);
        glCreateBuffers(1, &IndexBuffer);

        BinaryParser::FillBuffers(path, VBOs[0], VBOs[1], VBOs[2], IndexBuffer, IndexSize);
        
        glBindVertexBuffer(0, VBOs[0], 0, 24);
        glBindVertexBuffer(1, VBOs[1], 0, 8);
        glBindVertexBuffer(2, VBOs[2], 0, 24);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

    glBindVertexArray(0);

    return true;
}

void ZMeshData::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_SHORT, nullptr);
}
