#include "ZMesh.hpp"
#include <GL/glew.h>
#include <BinaryParser.hpp>
#include "OpenGEnum.hpp"
#include "AssetManager.hpp"

ZMesh::ZMesh()
:VAO(0)
{
    glGenVertexArrays(1, &VAO);
    //zmat = AssetManager::getMaterial("Default");
}

ZMesh::ZMesh(const ZMesh &orig){

}

ZMesh::~ZMesh(){
    //std::cout << "Deleting mesh..." << '\n';
    uint8_t i = VBOs.size();
    while(i--)  glDeleteBuffers(1, &VBOs[i]);

    glDeleteVertexArrays(1, &VAO);
}

bool ZMesh::load(const std::string& path, unsigned int type){

    bool loaded = BinaryParser::ImportMesh(path, Positions, UV_Coords, Normals, Tangents, Bitangents, Indexes);
    if(!loaded){
        std::cout << "   --No se pudo abrir " << path << '\n';
        return false;
    }

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indexes.size()*sizeof(unsigned short), &Indexes[0], GL_STATIC_DRAW);

    glBindVertexArray(VAO);
        addVertexBuffer(Positions,  type, 3, 0);
        addVertexBuffer(UV_Coords,  type, 2, 1);
        addVertexBuffer(Normals,    type, 3, 2);
        addVertexBuffer(Tangents,   type, 3, 3);
        addVertexBuffer(Bitangents, type, 3, 4);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBindVertexArray(0);

    return true;
}

void ZMesh::addVertexBuffer(std::vector<float> &data, unsigned int type, unsigned int DataLength, uint8_t layout){

    VBOs.push_back(0);


    glGenBuffers(1, &VBOs.back());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs.back());
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), &data[0], type == GN::STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(layout);
    glVertexAttribPointer(layout, DataLength, GL_FLOAT, GL_FALSE, 0, nullptr);

}