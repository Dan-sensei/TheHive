#include "ZMeshData.hpp"
#include <GL/glew.h>
#include "BinaryParser.hpp"
#include <Omicron/OpenGEnum.hpp>

ZMeshData::ZMeshData()
:VAO(0), IndexSize(0), VBO(0)
{
    glGenVertexArrays(1, &VAO);
}

ZMeshData::ZMeshData(const ZMeshData &orig)
:VAO(orig.VAO), IndexSize(orig.IndexSize)
{
    VBO = orig.VBO;
}

ZMeshData::~ZMeshData(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IndexBuffer);
    glDeleteVertexArrays(1, &VAO);
}

bool ZMeshData::load(const std::string& path){

    glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glVertexAttribFormat(0, 3, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, false, 12);
        glVertexAttribFormat(2, 2, GL_FLOAT, false, 24);
        glVertexAttribFormat(3, 3, GL_FLOAT, false, 32);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 0);
        glVertexAttribBinding(3, 0);

        glCreateBuffers(1, &VBO);
        glCreateBuffers(1, &IndexBuffer);

        BinaryParser::FillBuffers(path, VBO, IndexBuffer, IndexSize);

        glBindVertexBuffer(0, VBO, 0, 44);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

    glBindVertexArray(0);

    return true;
}

void ZMeshData::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_SHORT, nullptr);
}
