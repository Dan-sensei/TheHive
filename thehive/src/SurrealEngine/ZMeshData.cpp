#include "ZMeshData.hpp"
#include <GL/glew.h>
#include "BinaryParser.hpp"
#include "OpenGEnum.hpp"
#include <iostream>

ZMeshData::ZMeshData()
:VAO(0), IndexSize(0)
{
    glGenVertexArrays(1, &VAO);
}

ZMeshData::ZMeshData(const ZMeshData &orig){
    VAO = orig.VAO;
    IndexSize = orig.IndexSize;

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

    std::vector< float > PositionsNormals;
    std::vector< float > UV_Coords;
    std::vector< float > TangentsBitangents;
    std::vector< unsigned short > Indexes;

    bool loaded = BinaryParser::ImportMesh(path, PositionsNormals, UV_Coords, TangentsBitangents, Indexes);

    VBOs.reserve(3);

    if(!loaded){
        std::cout << "   --No se pudo abrir " << path << '\n';
        return false;
    }

    IndexSize = Indexes.size();


    glBindVertexArray(VAO);

        addVertexBuffer(PositionsNormals, 6);
        addVertexBuffer(UV_Coords, 2);
        addVertexBuffer(TangentsBitangents, 6);

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

        glBindVertexBuffer(0, VBOs[0], 0, 24);
        glBindVertexBuffer(1, VBOs[1], 0, 8);
        glBindVertexBuffer(2, VBOs[2], 0, 24);

        unsigned int IndexBuffer;
        glGenBuffers(1, &IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indexes.size()*sizeof(unsigned short), &(Indexes[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);

    return true;
}

void ZMeshData::addVertexBuffer(std::vector<float> &data, unsigned int DataLength){

    VBOs.push_back(0);

    glGenBuffers(1, &VBOs.back());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs.back());
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), &data[0], GL_STATIC_DRAW);
}

void ZMeshData::draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, IndexSize, GL_UNSIGNED_SHORT, nullptr);
}
